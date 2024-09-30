#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include "SDL2/include/SDL2/SDL.h"
#include "Wall.h"
#include "RVector.h"
#include "Player.h"

#define WIDTH 800
#define HEIGHT 800
#define SIZE 50
#define SPEED 600
#define GRAVITY 60
#define FPS 60
#define JUMP -1200

#define MAP_HEIGHT (SIZE * 3)
#define MAP_WIDTH (SIZE * 3)

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













    RVERTEX start_pos = {0, 0, 75};
    PLAYER* player = PLAYER_init_player(start_pos);



    int map[3][3] = { {0x00000000, 0xffffffff, 0x00000000},
                    {0x00000000, 0x00000000, 0x00000000},
                    {0x00000000, 0x00000000, 0x00000000} };

    SDL_Surface* surface = SDL_GetWindowSurface(wind);

    /* Main loop */
    float x_pos = (WIDTH - SIZE) / 2, y_pos = (HEIGHT - SIZE) / 2;
    SDL_Event event;
    while (true) {

        /* Process events */
        while (SDL_PollEvent(&event))
        {
            move_player(player, event, MAP_WIDTH, MAP_HEIGHT);
            PLAYER_rotate_camera(player, event);
            if (event.type == SDL_QUIT) {
                SDL_Quit();
             //   SDL_DestroyRenderer(rend);
             SDL_DestroyWindowSurface(wind);
                SDL_DestroyWindow(wind);
                return 0;
            }
        }
        SDL_LockSurface(surface);
        SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);
        SDL_UnlockSurface(surface);
        SDL_UpdateWindowSurface(wind);
        SDL_Delay(1000 / FPS);
    }
}

