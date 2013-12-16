#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <vector>
#include "commom.h"
#include "shot.h"


Shot::Shot(int x0, int y0, int d)
{
int i;
std::stringstream img_str;

    alive = true;
    posX = x0;
    posY = y0;
    dirX = d;
    speedX = (dirX == RIGHT) ? MAX_SHOT_SPEED : -MAX_SHOT_SPEED;
    screenWidthRef = x0+20 + SCREENWIDTH/2;

    img_prefix = "shot";

    for (i=0;i<images;i++) {
        img_str << "../img/" << img_prefix.c_str() << i << ".png";
        sprite.push_back(al_load_bitmap(img_str.str().c_str()));
        img_str.str("");
        mwidth += al_get_bitmap_width(sprite[i]);
        mheight += al_get_bitmap_height(sprite[i]);
    }

    mwidth = mwidth/i;
    mheight = mheight/i;
}

void Shot::Update()
{
    moveX();
    if (offSetX[dirX] != 0 || posX > screenWidthRef + 100 || posX < screenWidthRef - SCREENWIDTH - 100) {
        //printf("offSetX: %d, posX: %d\n", offSetX[dirX], posX);
        alive = false;
    }
    moveableObject::Update();
}

Shot::~Shot()
{
    //
}
