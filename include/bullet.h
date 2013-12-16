#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "moveableObject.h"

#define MAX_SHOT_SPEED  30

class Bullet : public moveableObject
{
    private:
    public:
        Bullet(int x0, int y0, int d);
        ~Bullet();
        void Update();

};
