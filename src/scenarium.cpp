#include <allegro5/allegro5.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include "commom.h"
#include "scenarium.h"

Scenarium::Scenarium(Player *p)
{
    player = p;
    level = 1;
    cameraPos[0] = cameraPos[1] = 0;
}

Scenarium::~Scenarium()
{
    cleanLevel();
    plats.~vector();
}

void Scenarium::moveCamera()
{
    cameraPos[0] = - (SCREENWIDTH/2) + (player->getPosX() + player->getWidth());
    //cameraPos[1] = - (SCREENHEIGHT/2) + (player->getPosY() + player->getHeight());

    if (cameraPos[0] < 0) cameraPos[0] = 0;
    if (cameraPos[1] < 0) cameraPos[1] = 0;

    al_identity_transform(&camera);
    al_translate_transform(&camera, -cameraPos[0], -cameraPos[1]);
    al_use_transform(&camera);
}

void Scenarium::Update()
{
int i;

    if (player->getPosX() > mapSizeX*BLOCK_SIZE)
        next_level = true;

    for (i=0; i < plats.size();i++)
        plats[i]->Update();
}

void Scenarium::cleanLevel()
{
int i;

    for (i=0; i < plats.size();i++) {
        plats[i]->~Platform();
    }
    plats.clear();
}

bool Scenarium::startLevel(int l)
{
int i, j;
Limits laux;
std::vector<Limits> lim;

    if (l > LEVELS) {
        printf("You Win!\n");
        return false;
    }

    level = l;

    cleanLevel();
    loadLevel();

    for (i=0;i < mapSizeX; i++) {
        for (j=0;j < mapSizeY; j++) {
            if (map[i][j] == 1)
                plats.push_back(new Platform(i * BLOCK_SIZE, j * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, al_map_rgb(0, 255, 0))); 
        }
    }
    
    // Fill collision limits to the player
    for (i=0; i < plats.size();i++) {
        laux.x0 = plats[i]->getPosX();
        laux.y0 = plats[i]->getPosY();
        laux.x1 = plats[i]->getPosX() + plats[i]->getWidth();
        laux.y1 = plats[i]->getPosY() + plats[i]->getHeight();
        lim.push_back(laux);
    }
    player->setLimits(lim);

    next_level = false;
    player->startLevel();

    return true;
}

void Scenarium::loadLevel()
{
int i,j,k;
std::stringstream map_str;
std::string line;

    map_str << "../maps/L" << level << ".txt";
    std::ifstream openfile(map_str.str().c_str());
    map_str.str("");

    if (openfile.is_open()) {
        
        std::getline(openfile, line);
        mapSizeX = line.length()/2;

        openfile.seekg(0, std::ios::beg);
        j=k=0;
        while (!openfile.eof()) {
            openfile >> map[j++][k]; 
            //printf("%d,%d = %d ",j-1,k, map[j-1][k]);
            if (j >= mapSizeX) { j=0; k++; }
            //if (k >= mapSizeY) break;
        }
        mapSizeY = k;

    } else {
        printf("Error on loading map %d \n", level);
        exit(1);
    }
    openfile.close();
}

bool Scenarium::nextLevel()
{
    return next_level;
}


