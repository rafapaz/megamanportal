#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "moveableObject.h"

#define MAX_SHOT_SPEED 30

class Shot : public moveableObject
{
    private:

    public:
        Shot(int x0, int y0, int d);
        ~Shot();
        void Update();

};
