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


#define WIDTH 800
#define HEIGHT 800
#define SIZE 500
#define SPEED 600
#define GRAVITY 60
#define FPS 60
#define JUMP -1200
#define MIN_BRIGHT 75

#define MAP_HEIGHT (BLOCK_SIZE * 3)
#define MAP_WIDTH (BLOCK_SIZE * 3)








void GAME_render_view(SDL_Window* wind, SDL_Surface* surface, SDL_Renderer* rend, PLAYER* player, int* map, int map_width) {

    SDL_LockSurface(surface);
    SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);


    RVECTOR h_iter;
    double x_incr = player->horizon.head.x - player->horizon.tail.x;
    double z_incr = player->horizon.head.z - player->horizon.tail.z;
    x_incr /= RVECTOR_length(player->horizon);
    z_incr /= RVECTOR_length(player->horizon);
    RVERTEX h_head = player->horizon.tail;
    h_iter.head = h_head;
    h_iter.tail = h_head;
    //h_iter = RVECTOR_normalize(h_iter);

//exit(0);
//printf("%.2lf\n\n"), RVECTOR_length(h_iter);

    for (int i = 0; i < 50; ++i) {
    //        RVECTOR_print(player->horizon);
    //RVECTOR_print(h_iter);
    //printf("%.2lf\n\n", RVECTOR_length(h_iter));
    RVERTEX plane_point = h_iter.head;
    RVECTOR ray;
    ray.head = plane_point;
    ray.tail = player->position.head;
    double ray_x_incr = ray.head.x - ray.tail.x;
    double ray_z_incr = ray.head.z - ray.tail.z;
    ray_x_incr /= RVECTOR_length(ray);
    ray_z_incr /= RVECTOR_length(ray);
    ray.head = ray.tail;
    ray.head.x += ray_x_incr;
    ray.head.z += ray_z_incr;

    DRAW_COL col = RVECTOR_cast_seek_length(rend, ray, plane_point, map, map_width);


       // int col_height = (int) (( col.distance / (double) MAP_HEIGHT) * (double) HEIGHT);
    int col_height = (int) col.distance;
    printf("%d\n", col_height);
    int half = col_height / 2;
    for (int k = (16*i); k < (16*(i + 1)); ++ k) {

    
        for (int j = col_height; j < HEIGHT - col_height; ++j) {
         //   uint32_t* pixels = (uint32_t*) surface->pixels;
       //         pixels[j * surface->w + k] = col.color;
       
        }
        h_iter.head.x += x_incr;
        h_iter.head.z += z_incr; 
    }
    }
//    SDL_UpdateWindowSurface(wind);
  //  SDL_UnlockSurface(surface);
   // exit(0);
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

    //Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    //SDL_Renderer *rend = SDL_CreateRenderer(wind, -1, render_flags);
    //SDL_Surface* surface = SDL_GetWindowSurface(wind);
    //SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
    //SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
  //  if (!rend)
   // {
    //  printf("Error creating renderer: %s\n", SDL_GetError());
     // SDL_DestroyWindow(wind);
     // SDL_Quit();
     // return 0;
   // }






    RVERTEX start_pos = {300, 0, 300};
    PLAYER* player = PLAYER_init_player(start_pos);


   // uint32_t map[25] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
     //              0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF,
       //             0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF,
         //         0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF,
           //      0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
                    
    uint32_t map[9] = { 0x00000099, 0x00000099, 0x00000099,
                    0x00000099, 0x00000000, 0x00000099,
                        0x00000099, 0x00000099, 0x00000099};;

    SDL_Surface* surface = SDL_GetWindowSurface(wind);
   // SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    /* Main loop */
    float x_pos = (WIDTH - BLOCK_SIZE) / 2, y_pos = (HEIGHT - BLOCK_SIZE) / 2;
    SDL_Event event;
    while (true) {

        /* Process events */
        while (SDL_PollEvent(&event))
        {
        ////    move_player(player, event, map, 3, 3);
            PLAYER_rotate_camera(player, event);

            if (event.type == SDL_QUIT) {
                SDL_Quit();
             //   SDL_DestroyRenderer(rend);
                SDL_DestroyWindowSurface(wind);
                SDL_DestroyWindow(wind);
                return 0;
            }
        }
    //SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
   // SDL_RenderClear(rend);
        SDL_Rect rect;
        rect.h = 10;
        rect.w = 10;
        rect.x = (int) player->position.head.x;
        rect.y = (int) player->position.head.z;
      // SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
       GAME_render_view(wind, surface, NULL, player, map, 3);

      for (int i = 0; i < 600; i += BLOCK_SIZE) {
        for (int j = 0; j < 600; j += BLOCK_SIZE) {
          SDL_Rect this;
          this.y = i;
          this.x = j;
          this.h = BLOCK_SIZE;
          this.w = BLOCK_SIZE;
          SDL_RenderDrawRect(rend, &this);
        }
      }

        //SDL_RenderDrawRect(rend, &rect);
        //SDL_RenderDrawLine(rend, player->horizon.head.x, player->horizon.head.z, player->horizon.tail.x, player->horizon.tail.z);
    //SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
  //SDL_RenderDrawLine(rend, player->dir_vector.head.x, player->dir_vector.head.z, player->dir_vector.tail.x, player->dir_vector.tail.z);
       // printf("%d %d\n", rect.x, rect.y);
     //   SDL_RenderPresent(rend);

       // SDL_LockSurface(surface);
      //  SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);
     //   SDL_UnlockSurface(surface);
   //     SDL_UpdateWindowSurface(wind);
        SDL_Delay(1000 / FPS);
    }
}

