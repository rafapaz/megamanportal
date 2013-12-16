#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <iostream>
#include <vector>
#include "commom.h"
#include "moveableObject.h"

moveableObject::moveableObject()
{
    images = 1;
    spriteId = 0;
    speedX = 0;
    speedY = 0;
    posX = 0;
    posY = 0;
    mwidth = 0;
    mheight = 0;
    dirX = 0;
    dirY = 0;
    offSetX[RIGHT] = 0;
    offSetX[LEFT] = 0;
    offSetY[UP] = 0;
    offSetY[DOWN] = 0;
    screenWidthRef = 0;
    alive = true;
    chSprite = false;

    mwidth = 0;
    mheight = 0;

}

moveableObject::~moveableObject()
{
int i;

    //std::cout << "Deleting object: " << img_prefix.c_str() << "\n";
    
    for (i=0;i < images; i++)
        al_destroy_bitmap(sprite[i]);
}


void moveableObject::moveX() 
{
    posX += speedX;
    checkCollision();
    posX -= offSetX[dirX];
}

void moveableObject::moveY()
{
    posY += speedY;
    checkCollision();
    posY -= offSetY[dirY];
}

void moveableObject::startMoveX(int d) 
{
    dirX = d;
}

void moveableObject::startMoveY(int d) 
{
    dirY = d;
}

void moveableObject::stopMoveX(int d) 
{
    //
}

void moveableObject::checkCollision()
{
int i;

    offSetX[RIGHT] = 0;
    offSetX[LEFT] = 0;
    offSetY[UP] = 0;
    offSetY[DOWN] = 0;

    for (i=0;i < limits.size();i++) {
        if (posX + mwidth > limits[i].x0 && posX < limits[i].x1 && 
                posY + mheight > limits[i].y0 && posY < limits[i].y1) {

            offSetX[RIGHT] = (posX + mwidth) - limits[i].x0;
            offSetX[LEFT] = -(limits[i].x1 - posX);
            offSetY[UP] = -(limits[i].y1 - posY);
            offSetY[DOWN] = (posY + mheight) - limits[i].y0;
        }
    }

}

void moveableObject::setLimits(std::vector<Limits> lim)
{
    limits = lim;
}

void moveableObject::Update()
{
    al_draw_bitmap(sprite[spriteId], posX, posY, 0);
}

void moveableObject::printStates()
{
    printf("\n");
    printf("dirX = %d; dirY = %d; posX = %d; posY = %d; speedX = %d; speedY = %d; spriteId = %d\n", dirX, dirY, posX, posY, speedX, speedY, spriteId);
    printf("\n");
}

void moveableObject::startLevel()
{
    posX = posY = 0;
}

void moveableObject::changeSprite()
{
    chSprite = true;
}

// GETS AND SETS
int moveableObject::getPosX() { return posX; }
int moveableObject::getPosY() { return posY; }
int moveableObject::getWidth() { return mwidth; } //al_get_bitmap_width(sprite[spriteId]); }
int moveableObject::getHeight() { return mheight; } // al_get_bitmap_height(sprite[spriteId]); }
int moveableObject::getSpeedX() { return speedX; }
int moveableObject::getSpeedY() { return speedY; }
bool moveableObject::isAlive() { return alive; }
