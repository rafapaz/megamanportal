#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <vector>
#include "commom.h"
#include "player.h"


Player::Player()
{
int i;
std::stringstream img_str;

    img_prefix = "player";
    images = 16;

    img_ground[RIGHT] = 0;
    img_ground[LEFT] = 4;
    img_jump[RIGHT] = 8;
    img_jump[LEFT] = 9;
    img_ground_shot[RIGHT] = 10;
    img_run_shot[RIGHT] = 11;
    img_ground_shot[LEFT] = 12;
    img_run_shot[LEFT] = 13;
    img_jump_shot[RIGHT] = 14;
    img_jump_shot[LEFT] = 15;

    portal[IN].x0 = 0;
    portal[IN].x1 = 0;
    portal[IN].y0 = 0;
    portal[IN].y1 = 0;

    portal[OUT].x0 = 0;
    portal[OUT].x1 = 0;
    portal[OUT].y0 = 0;
    portal[OUT].y1 = 0;

    spriteId = img_ground[RIGHT];
    speedX = MAX_SPEED_X;
    speedY = MAX_SPEED_Y;
    posX = 0;
    posY = 0;
    mwidth = 0;
    mheight = 0;
    dirX = RIGHT;
    dirY = DOWN;
    offSetX[RIGHT] = 0;
    offSetX[LEFT] = 0;
    offSetY[UP] = 0;
    offSetY[DOWN] = 0;
    alive = true;
    chSprite = false;
    bullet = NULL;
    ground = false;
    inPortal = false;
    mode = IN;


    for (i=0;i<images;i++) {
        img_str << "../img/" << img_prefix.c_str() << i << ".png";
        sprite.push_back(al_load_bitmap(img_str.str().c_str()));
        img_str.str("");
        mwidth += al_get_bitmap_width(sprite[i]);
        mheight += al_get_bitmap_height(sprite[i]);
    }

    mwidth = mwidth/i;
    mheight = mheight/i;

    width1 = mwidth;
    width2 = 0;

    printf("Player initialized!\n");
}


void Player::moveX() 
{
int m;

    moveableObject::moveX();

    if (chSprite) {
        spriteId = runNumber(spriteId, img_ground[dirX]+1, img_ground[dirX] + SPRITE_INTERVAL);
        chSprite = false;
    }
    
    /*
    for (m=IN; m<=OUT;m++) {
        if (posX + mwidth > portal[m].x0 && posX < portal[m].x1 && 
                posY + mheight > portal[m].y0 && posY < portal[m].y1) {
            inPortal = true;
            posX = portal[!m].x0;
            posY = portal[!m].y1 - mheight;
        } else {
            inPortal = false;
        }
    }
    */
}

void Player::moveY()
{
    speedY += GRAVITY;
    if (speedY < -MAX_SPEED_Y) speedY = -MAX_SPEED_Y; 
    else if (speedY > MAX_SPEED_Y) speedY = MAX_SPEED_Y;

    moveableObject::moveY();

    if (dirY == UP && speedY >= 0)
        startMoveY(DOWN);

    if (!ground)
        spriteId = img_jump[dirX];

    if (!ground && dirY==DOWN && offSetY[DOWN]!=0)  {
        ground = true;
        spriteId = img_ground[dirX];
    } else if (dirY==DOWN && offSetY[DOWN]==0) {
        ground = false;
    }
}

void Player::startMoveX(int d) 
{
    moveableObject::startMoveX(d);
    spriteId = img_ground[dirX];
    speedX = (dirX == RIGHT) ? MAX_SPEED_X : -MAX_SPEED_X ;
}

void Player::startMoveY(int d) 
{
    if (d==UP && !ground) return; //avoid jump twice in the air
    moveableObject::startMoveY(d);
    speedY = (dirY == UP) ? -MAX_SPEED_Y : MAX_SPEED_Y;
    spriteId = img_jump[dirX];
    ground = false;
}

void Player::stopMoveX(int d) 
{
    spriteId = img_ground[dirX];
}

void Player::Update()
{
    if (posY > SCREENHEIGHT)
        alive = false;

    if (bullet != NULL) {
        bullet->Update();
        if (!bullet->isAlive()) {
            openPortal();
            delete bullet;
            bullet = NULL;
        }
    }

    screenWidthRef = posX + (mwidth/2) + (SCREENWIDTH/2);
    moveableObject::Update();

    al_draw_filled_rectangle(portal[IN].x0,portal[IN].y0,portal[IN].x1,portal[IN].y1, al_map_rgb(0,0, 255));
    al_draw_filled_rectangle(portal[OUT].x0,portal[OUT].y0,portal[OUT].x1,portal[OUT].y1, al_map_rgb(128,0, 128));
}

void Player::startLevel()
{
    posX = posY = 0;
}

void Player::Shot()
{
int px;

    if (bullet != NULL) return;

    px = (dirX == RIGHT) ? posX + mwidth + 10: posX - 30;
    bullet = new Bullet(px, posY + 40, dirX);
    bullet->setLimits(limits);

    spriteId = (ground) ? img_ground_shot[dirX] : img_jump_shot[dirX];
}

void Player::openPortal()
{
    portal[mode].x0 = bullet->getPosX();
    portal[mode].x1 = bullet->getPosX() + 10;
    portal[mode].y0 = bullet->getPosY() - PORTAL_HEIGHT/2;
    portal[mode].y1 = bullet->getPosY() + PORTAL_HEIGHT/2;

    mode = !mode;
}
