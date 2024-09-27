#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include "SDL2/include/SDL2/SDL.h"
#include "Wall.h"

#define WIDTH 800
#define HEIGHT 800
#define SIZE 1
#define SPEED 600
#define GRAVITY 60
#define FPS 60
#define JUMP -1200


void move_player(SDL_Event event, WALL* wall);

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

    /* Create a renderer */
   // Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    //SDL_Renderer *rend = SDL_CreateRenderer(wind, -1, render_flags);
    SDL_Surface* surface = SDL_GetWindowSurface(wind);
    //SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
   // if (!rend)
   // {
   //     printf("Error creating renderer: %s\n", SDL_GetError());
   //     SDL_DestroyWindow(wind);
   //     SDL_Quit();
   //     return 0;
   // }

    /* Main loop */
    float x_pos = (WIDTH - SIZE) / 2, y_pos = (HEIGHT - SIZE) / 2;
    SDL_Rect* rect = (SDL_Rect*) malloc(sizeof(SDL_Rect));
    WALL wall = {x_pos, y_pos, SIZE, SIZE, 0xFFFF00FF};

    rect->h = SIZE;
    rect->w = 700;
    rect->x = x_pos;
    rect->y = y_pos;
    SDL_Event event;
    while (true) {

    
        /* Process events */
        while (SDL_PollEvent(&event))
        {
            move_player(event, &wall);
            if (event.type == SDL_QUIT) {
                SDL_Quit();
             //   SDL_DestroyRenderer(rend);
             SDL_DestroyWindowSurface(wind);
                SDL_DestroyWindow(wind);
                return 0;
            }
        }
        /* Clear screen */
      //  SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
       // SDL_RenderClear(rend);
        SDL_LockSurface(surface);
        SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);
        SDL_UnlockSurface(surface);

        WALL_render(wall, surface);
        SDL_UpdateWindowSurface(wind);
        /* Draw the rectangle */
      //  SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
       // SDL_RenderFillRect(rend, rect);

        /* Draw to window and loop */
     //   SDL_RenderPresent(rend);
        SDL_Delay(1000 / FPS);
    }
}

void move_player(SDL_Event event, WALL* wall) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_W:
            wall->h += 2;
            wall->w += 2;
         //   if ((wall->color & 0x000000FF) < 0xFF) {
         //       wall->color += 1;
         //   }
            break;

        case SDL_SCANCODE_S:
            wall->h -= 2;
            wall->w -= 2;
         //   if ((wall->color & 0x000000FF) >= 0x00)
          //  {
          //      wall->color -= 1;
          //  }
            break;
        default:
            break;
        }
        wall->x = (WIDTH - wall->w) / 2;
        wall->y = (HEIGHT - wall->h) / 2;
    }

}