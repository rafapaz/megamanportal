#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <vector>

#define MAX_SPEED_X 7
#define MAX_SPEED_Y 20
#define SPRITE_INTERVAL 4
#define IMAGES 10

enum { RIGHT, LEFT };        // X direction
enum { UP, DOWN };    // Y direction
enum { IMG_RIGHT=0, IMG_LEFT=4, IMG_RIGHT_JUMP=8, IMG_LEFT_JUMP=9};

class Player
{
    private:
        int posX;
        int posY;
        int mwidth;
        int mheight;
        int speedX;
        int speedY;
        int dirX;
        int dirY;
        int spriteId;
        int offSetX[2];
        int offSetY[2];
        bool alive;
        bool chSprite;
        std::vector<Limits> limits;
        
        ALLEGRO_BITMAP *sprite[IMAGES];
        void checkCollision();

    public:
        Player();
        ~Player();
        void Update();
        int getPosX();
        int getPosY();
        int getWidth();
        int getHeight();
        int getSpeedX();
        int getSpeedY();
        void moveX();
        void moveY();        
        void startMoveX(int d);
        void startMoveY(int d);        
        void stopMoveX(int d);
        void setLimits(std::vector<Limits> lim);
        bool isAlive();
        void changeSprite();
        void startLevel();
        void printStates();
};
