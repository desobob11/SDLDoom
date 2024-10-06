#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
#include "SDL2/include/SDL2/SDL.h"
#include "Wall.h"
#include "RVector.h"
#include "Player.h"
#include <math.h>
#include <unistd.h>
#include "Const.h"
#include "Game.h"
#include "Automap.h"


#define SPEED 600
#define FPS 60

#define MAP_HEIGHT (BLOCK_SIZE * 5)
#define MAP_WIDTH (BLOCK_SIZE * 5)


extern int DRAW_MODE;
int DRAW_MODE = 0;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;




int main(int argc, char *argv[])
{
    /* Initializes the timer, audio, video, joystick,
    haptic, gamecontroller and events subsystems */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }
    /* Create a window */
    SDL_Window *wind = SDL_CreateWindow("SDoomL",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!wind)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(wind);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    if (!surface)
    {
      printf("Error creating surface: %s\n", SDL_GetError());
      SDL_DestroyWindow(wind);
      SDL_Quit();
      return 0;
    }






    RVERTEX start_pos = {500, 0, 500};
    PLAYER* player = PLAYER_init_player(start_pos);

    MAP map_;
    map_.h = 5;
    map_.w = 5;
    
    uint32_t map[25] = { 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
                   0x00FFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00FFFFFF,
                    0x00FFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00FFFFFF,
                  0x00FFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00FFFFFF,
                 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF};
     map_.map = map;


    SDL_Event event;
    while (true) {

        /* Process events */
        while (SDL_PollEvent(&event))
        {

            PLAYER_rotate_camera(player, event);

            if (event.type == SDL_QUIT) {
                SDL_Quit();
                SDL_DestroyWindowSurface(wind);
                SDL_DestroyWindow(wind);
                return 0;
            }
        }
        SDL_Rect rect;
        rect.h = 10;
        rect.w = 10;
        rect.x = (int) player->position.head.x;
        rect.y = (int) player->position.head.z;
        GAME_render_view(wind, surface, NULL, player, map_.map, 5);
        SDL_Delay(1000 / FPS);
    }
}

