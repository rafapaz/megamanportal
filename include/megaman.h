
#define GAME_NAME "Megaman Portal"
#define VERSION 0.1

enum { ERR_ALLEGRO, ERR_DISPLAY, ERR_TIMER };

void init();
void main_loop();
void destroy();

char *getTitle();
void initErrorMsg();
void alert(int err);

int getSpeed(int64_t t0);
