#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "bullet.h"

#define MAX_SPEED_X 7
#define MAX_SPEED_Y 20
#define SPRITE_INTERVAL 3
#define PORTAL_HEIGHT   100

enum { IN, OUT };

class Player : public moveableObject {
    private:
        int img_ground[2];
        int img_ground_shot[2];
        int img_run_shot[2];
        int img_jump[2];
        int img_jump_shot[2];
        int mode;

        int width1;
        int width2;

        bool ground;
        bool inPortal;
        Bullet *bullet;
        Limits portal[2];
    public:
        Player();
        ~Player();
        void startLevel();
        void printStates();
        void moveX();
        void moveY();        
        void startMoveX(int d);
        void startMoveY(int d);        
        void stopMoveX(int d);
        void Shot();
        void openPortal();
        void Update();
};
