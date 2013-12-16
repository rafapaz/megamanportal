#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <vector>

enum { RIGHT, LEFT }; // X direction
enum { UP, DOWN };    // Y direction

class moveableObject
{
    protected:
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
        int screenWidthRef;
        int images;
        bool alive;
        bool chSprite;
        std::vector<Limits> limits;
        std::vector<ALLEGRO_BITMAP *> sprite;
        std::string img_prefix;

        void checkCollision();

    public:
        moveableObject();
        ~moveableObject();
        int getPosX();
        int getPosY();
        int getWidth();
        int getHeight();
        int getSpeedX();
        int getSpeedY();
        void setLimits(std::vector<Limits> lim);
        bool isAlive();
        void changeSprite();
        void printStates();
        void startLevel();
        virtual void moveX();
        virtual void moveY();        
        virtual void startMoveX(int d);
        virtual void startMoveY(int d);        
        virtual void stopMoveX(int d);
        virtual void Update();
};

