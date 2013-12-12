#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include "commom.h"
#include "platform.h"

Platform::Platform(int x, int y, int w, int h, ALLEGRO_COLOR c)
{
    posX = x;
    posY = y;
    width = w;
    height = h;
    color = c;

    img = NULL;
}

Platform::Platform(int x, int y, std::string img_path)
{
    posX = x;
    posY = y;

    img = al_load_bitmap(img_path.c_str());
    color = al_map_rgb(255, 0, 0);

}

void Platform::Update()
{
    if (img == NULL) {
        al_draw_filled_rectangle(posX, posY, posX + width, posY + height, color);
        return;
    }
    al_draw_bitmap(img, posX, posY, 0);

}

Platform::~Platform()
{
    if (img != NULL)
        al_destroy_bitmap(img);
}


// GETS AND SETS
int Platform::getPosX() { return posX; }
int Platform::getPosY() { return posY; }
int Platform::getWidth() { return width; }
int Platform::getHeight() { return height; }
