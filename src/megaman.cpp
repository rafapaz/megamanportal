#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "commom.h"
#include "megaman.h"
#include "scenarium.h"

// GLOBALS
ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;
ALLEGRO_TIMER *playerTimer;
Player *player;
Scenarium *map;


// AUX FUNCTIONS
char *getTitle()
{
    char *s = NULL;
    s = (char *) malloc(sizeof(char)*256);
    memset(s,'\0',256);
    sprintf(s,"%s V: %.1f", GAME_NAME, VERSION);
    return s;
}

void alert(int code)
{
    char *msg;

    switch (code)
    {
    case ERR_ALLEGRO:
        msg = strdup("Could not initialize Allegro 5");
    break;
    case ERR_DISPLAY:
        msg = strdup("Could not initialize Display object");
    break;
    case ERR_TIMER:
        msg = strdup("Could not create timer");
    break;
    }

    al_show_native_message_box(NULL,NULL,"ALERT:",msg,NULL,0);
    free(msg);
}


// 3 MAIN FUNCTIONs
void init()
{
    char *title;

    title = getTitle();
    printf("%s \n", title);

    // Init Allegro
    if (!al_init())
    {
        alert(ERR_ALLEGRO);
        exit(1);
    }

    // Display
    display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
    if (!display)
    {
        alert(ERR_DISPLAY);
        exit(1);
    }
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    al_set_window_position(display, 10, 30);
    al_set_window_title(display, title); 

    // Drawings
    al_init_primitives_addon();
    al_init_image_addon();

    // Timer
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        alert(ERR_TIMER);
        exit(1);
    }
    // Player Timer
    playerTimer = al_create_timer(1.0 / playerFPS);
    if(!playerTimer) {
        alert(ERR_TIMER);
        exit(1);
    }

    // Events
    event_queue = NULL;
    event_queue = al_create_event_queue();
    al_install_keyboard();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(playerTimer));

    //Player
    player = new Player();

    //Scenarium
    map = new Scenarium(player);

    free(title);
    printf("Game initialized!\n");
}

void destroy()
{
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_timer(playerTimer);

    printf("Game finished!\n");
}

void main_loop()
{
bool done = false;
bool redraw = true;
bool debug = false;
int level = 0;
ALLEGRO_KEYBOARD_STATE keyState;

    al_start_timer(timer);
    al_start_timer(playerTimer);

    while (!done)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            done = true;
        }

        if (event.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch (event.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                break;
                case ALLEGRO_KEY_SPACE:
                    player->startMoveY(DOWN);
                break;
                case ALLEGRO_KEY_LEFT:
                    player->stopMoveX(LEFT);
                break;
                case ALLEGRO_KEY_RIGHT:
                    player->stopMoveX(RIGHT);
                break;
            }
        }
        
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {

            switch (event.keyboard.keycode)
            {
            case ALLEGRO_KEY_LEFT:
                player->startMoveX(LEFT);
            break;
            case ALLEGRO_KEY_RIGHT:
                player->startMoveX(RIGHT);
            break;
            case ALLEGRO_KEY_SPACE:
                player->startMoveY(UP);
            break;
            case ALLEGRO_KEY_X:
                player->Shot();
            break;
            }

        }
        
        if (event.type == ALLEGRO_EVENT_TIMER) {

            if (level == 0 || map->nextLevel())
                if (!map->startLevel(++level))
                    done = true;

            al_get_keyboard_state(&keyState);

            if (event.timer.source == playerTimer)
                player->changeSprite();

            if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) || al_key_down(&keyState, ALLEGRO_KEY_LEFT)) //{
                player->moveX();
            
            player->moveY();

            //map->moveCamera();

            if (!player->isAlive()) done = true; 
            redraw = true;
        }
        

        if (redraw && al_is_event_queue_empty(event_queue)) 
        {
            redraw = false;
            player->Update();
            map->Update();
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }
}

int main(int argc, char **argv)
{
    init();
    main_loop();
    destroy();

    return(0);
}
