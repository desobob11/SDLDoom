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

#define WIDTH 800
#define HEIGHT 800
#define SIZE 1600
#define SPEED 600
#define GRAVITY 60
#define FPS 60
#define JUMP -1200
#define MIN_BRIGHT 75

#define MAP_HEIGHT (SIZE * 3)
#define MAP_WIDTH (SIZE * 3)





void GAME_render_view(SDL_Window* wind, SDL_Surface* surface, PLAYER* player, int* map, int map_width) {
    SDL_LockSurface(surface);
      SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);

    RVECTOR turn_vec = player->dir_vector;
    SDL_Color col;
    col.a = 0x99;
    col.r = 0xFF;
    col.g = 0xFF;
    col.b = 0xFF;
    
    double dir = player->direction - (M_PI / 8);
    if (dir < 0)
        dir += (2.0 * M_PI);
    turn_vec.head.x = player->position.head.x + cos(dir);
    turn_vec.head.z = player->position.head.z + sin(dir);

    //RVECTOR_print(turn_vec);
    //printf("DIR %.2lf %.2lf %.2lf\n", dir, dir / M_PI, RVECTOR_length(turn_vec));
    
    for (int i = 0; i < WIDTH; ++i) {

    DRAW_COL col = RVECTOR_cast_seek_length(turn_vec, player->horizon, map, map_width);


       // int col_height = (int) (( col.distance / (double) MAP_HEIGHT) * (double) HEIGHT);
       int col_height = (int) col.distance;
    int half = col_height / 2;

        for (int j = col_height; j < HEIGHT - col_height; ++j) {
            //  printf("here\n");
            uint32_t* pixels = (uint32_t*) surface->pixels;
                pixels[j * surface->w + i] = col.color;
       
        }
        


        dir -= (M_PI / 1600);
    turn_vec.head.x = player->position.head.x + cos(dir);
    turn_vec.head.z = player->position.head.z + sin(dir);
    }
    SDL_UpdateWindowSurface(wind);
    SDL_UnlockSurface(surface);
}

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
                                        WIDTH, HEIGHT, 0);
    if (!wind)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }







    RVERTEX start_pos = {75, 0, 75};
    PLAYER* player = PLAYER_init_player(start_pos);


    uint32_t map[9] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                    0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
                    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
                    
    //uint32_t map[9] = { 0x00000099, 0x00000099, 0x00000099,
      //              0x00000099, 0x00000000, 0x00000099,
        //            0x00000099, 0x00000099, 0x00000099};;

    SDL_Surface* surface = SDL_GetWindowSurface(wind);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    /* Main loop */
    float x_pos = (WIDTH - SIZE) / 2, y_pos = (HEIGHT - SIZE) / 2;
    SDL_Event event;
    while (true) {

        /* Process events */
        while (SDL_PollEvent(&event))
        {
            move_player(player, event, map, 3, 3);
            PLAYER_rotate_camera(player, event);

            if (event.type == SDL_QUIT) {
                SDL_Quit();
             //   SDL_DestroyRenderer(rend);
             SDL_DestroyWindowSurface(wind);
                SDL_DestroyWindow(wind);
                return 0;
            }
        }
        GAME_render_view(wind, surface, player, map, 3);
       // SDL_LockSurface(surface);
      //  SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);
     //   SDL_UnlockSurface(surface);
       // SDL_UpdateWindowSurface(wind);
        SDL_Delay(1000 / FPS);
    }
}

