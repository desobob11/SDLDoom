#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
#include "SDL2/include/SDL2/SDL.h"
#include "Wall.h"
#include "RVector.h"
#include "Player.h"
#include <math.h>
#include "Const.h"
#include "Game.h"
#include "Automap.h"


#define SPEED 600
#define FPS 60

#define MAP_HEIGHT (BLOCK_SIZE * 7)
#define MAP_WIDTH (BLOCK_SIZE * 7)


extern int DRAW_MODE;
int DRAW_MODE = 0;








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






    RVERTEX start_pos = {900, 0, 900};
    PLAYER* player = PLAYER_init_player(start_pos);

    current_map.h = 7;
    current_map.w = 7;

    uint32_t map[49] = {0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF,
                        0x00FFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0x00FFFFFF,
                        0x00FFFFFF, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FFFFFF,
                        0x00FFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FFFFFF,
                        0x00FFFFFF, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FFFFFF,
                        0x00FFFFFF, 0x0000FF00, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FFFFFF,
                        0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF};
    current_map.map = map;

    current_map.v_h = current_map.h * BLOCK_SIZE;
    current_map.v_w = current_map.w * BLOCK_SIZE;

    SDL_Event event;
    while (true) {
      SDL_UpdateWindowSurface(wind);
        /* Process events */
        while (SDL_PollEvent(&event))
        {
           // PLAYER_move_player(player, event, current_map.map, 7, 7);
            //PLAYER_rotate_camera(player, event);

            if (event.type == SDL_KEYDOWN)
            {
                SDL_Scancode code = event.key.keysym.scancode;

                if (code == SDL_SCANCODE_TAB) {
                    RENDER_MDOE = !RENDER_MDOE;
                }
            }

            if (event.type == SDL_QUIT) {
                SDL_Quit();
                SDL_DestroyWindowSurface(wind);
                SDL_DestroyWindow(wind);
                return 0;
            }
        }

            PLAYER_move_player(player, event, current_map.map, 7, 7);
            PLAYER_rotate_camera(player, event);
        if (RENDER_MDOE == 0) {
            GAME_render_view(wind, surface, NULL, player, current_map.map, 7);
        }
        else {
            AUTOMAP_render_map(wind, surface, current_map.map, player);
        }
        SDL_Delay(1000 / FPS);
    }
}

