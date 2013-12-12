#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <string>

class Platform
{
    private:
        int width;
        int height;
        int posX;
        int posY;

        ALLEGRO_BITMAP *img;
        ALLEGRO_COLOR color;
    public:
        Platform(int x, int y, int w, int h, ALLEGRO_COLOR c);
        Platform(int x, int y, std::string img_path);
        ~Platform();
        void Update();
        int getPosX();
        int getPosY(); 
        int getWidth();
        int getHeight();
};

