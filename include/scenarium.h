#include <allegro5/allegro5.h>
#include <vector>
#include "platform.h"
#include "player.h"

#define BLOCK_SIZE 50
#define LEVELS 2
#define MAP_MAX_WIDTH 10000
#define MAP_MAX_HEIGHT 512

class Scenarium
{
    private:
        int level;
        int mapSizeX, mapSizeY;
        int map[MAP_MAX_WIDTH][MAP_MAX_HEIGHT];
        int cameraPos[2];
        bool next_level;
        std::vector<Platform *> plats;
        Player *player;
        ALLEGRO_TRANSFORM camera;

        void loadLevel();
        void cleanLevel();
        inline bool haveCollision(int px, int py, int pw, int ph, int ex, int ey, int ew, int eh);
    public:
        Scenarium(Player *p);
        ~Scenarium();
        void Update();
        bool startLevel(int l);
        bool nextLevel();
        void moveCamera();
};
