#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
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

    spriteId = IMG_RIGHT;
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

    for (i=0;i<IMAGES;i++) {
        img_str << "../img/" << i << ".png";
        sprite[i] = al_load_bitmap(img_str.str().c_str());
        img_str.str("");
        mwidth += al_get_bitmap_width(sprite[i]);
        mheight += al_get_bitmap_height(sprite[i]);
    }

    mwidth = mwidth/i;
    mheight = mheight/i;
    
    printf("Player initialized");
}


void Player::moveX() 
{
    posX += speedX;
    checkCollision();
    posX -= offSetX[dirX];

    //printf("dirY: %d, offSetY: %d\n", dirY, offSetY[dirY]);
    if (chSprite) {
        if (dirX == RIGHT) {
           spriteId++;
           if (spriteId >= IMG_RIGHT + SPRITE_INTERVAL)
               spriteId = IMG_RIGHT+1;
        } else {
           spriteId++;
           if (spriteId >= IMG_LEFT + SPRITE_INTERVAL) 
               spriteId = IMG_LEFT+1;
        }
        chSprite = false;
    }
}

void Player::moveY()
{
    speedY += GRAVITY;
    if (speedY < -MAX_SPEED_Y) speedY = -MAX_SPEED_Y; 
    else if (speedY > MAX_SPEED_Y) speedY = MAX_SPEED_Y;

    posY += speedY;
    checkCollision();
    posY -= offSetY[dirY];

    if (dirY == UP && speedY >= 0)
        startMoveY(DOWN);

}

void Player::startMoveX(int d) 
{
    dirX = d;
    
    if (dirX == RIGHT) {
        speedX = MAX_SPEED_X;
        spriteId = IMG_RIGHT;
    } else {
        speedX = -MAX_SPEED_X;
        spriteId = IMG_LEFT;
    }
}

void Player::startMoveY(int d) 
{
    dirY = d;
    if (dirY == UP) speedY = -MAX_SPEED_Y;
    else if (dirY == DOWN) speedY = MAX_SPEED_Y;
    else speedY = 0;

}

void Player::stopMoveX(int d) 
{
    if (d == RIGHT)
        spriteId = IMG_RIGHT;
    else
        spriteId = IMG_LEFT;
}

void Player::checkCollision()
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

void Player::setLimits(std::vector<Limits> lim)
{
    limits = lim;
}

void Player::Update()
{
    if (posY > SCREENHEIGHT)
        alive = false;

    al_draw_bitmap(sprite[spriteId], posX, posY, 0);
}

Player::~Player()
{
int i;

    for (i=0;i<IMAGES;i++) {
        al_destroy_bitmap(sprite[i]);
    }
}

void Player::printStates()
{
    printf("\n");
    printf("\n");
}

void Player::startLevel()
{
    posX = posY = 0;
}

void Player::changeSprite()
{
    chSprite = true;
}

// GETS AND SETS
int Player::getPosX() { return posX; }
int Player::getPosY() { return posY; }
int Player::getWidth() { return mwidth; } //al_get_bitmap_width(sprite[spriteId]); }
int Player::getHeight() { return mheight; } // al_get_bitmap_height(sprite[spriteId]); }
int Player::getSpeedX() { return speedX; }
int Player::getSpeedY() { return speedY; }
bool Player::isAlive() { return alive; }
