#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include "SDL2/include/SDL2/SDL.h"
#include "Wall.h"
#include "RVector.h"
#include "Player.h"
#include <math.h>

#define WIDTH 800
#define HEIGHT 800
#define SIZE 50
#define SPEED 600
#define GRAVITY 60
#define FPS 60
#define JUMP -1200
#define MIN_BRIGHT 75

#define MAP_HEIGHT (SIZE * 4)
#define MAP_WIDTH (SIZE * 4)

void GAME_render_column(WALL wall, SDL_Surface* surface) {

    
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    SDL_LockSurface(surface);
    SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);
    for (int i = wall.x; i < wall.x + wall.w; ++i) {
        for (int j = wall.y; j < wall.y + wall.h; ++j) {
 
            uint32_t* pixels = (uint32_t*) surface->pixels;
            pixels[j * surface->w + i] = wall.color;
            // uint32_t* pixel = (uint32_t* ) ((uint8_t* ) surface->pixels
            //  + (wall.y + j) * surface->pitch + (wall.x * i) * surface->format->BitsPerPixel);

            //if (*pixel != wall.color) {
          //      *pixel = wall.color;
          //  }
        }
    }
    SDL_UnlockSurface(surface);
}

/*
void GAME_render_view(SDL_Window* wind, SDL_Surface* surface, PLAYER* player, int* map, int map_width) {
    SDL_LockSurface(surface);
      SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);
    
    RVECTOR turn_vec = player->dir_vector;
    double dir = M_PI / 8;
    RVERTEX dir_head = {player->position.head.x + cos(dir), 0, player->position.head.z + sin(dir)};
    turn_vec.head = dir_head;
    //for (int i = 0; i < WIDTH; ++i) {
    int i = WIDTH / 2;
        DRAW_COL col = RVECTOR_cast_seek_length(turn_vec, map, map_width);
        dir -= (M_PI / 1600);
        dir_head.x = player->position.head.x + cos(dir);
        dir_head.z = player->position.head.z + sin(dir);
        turn_vec.head = dir_head;

        
    
    int col_height = (int) (( col.distance / (double) MAP_HEIGHT) * (double) HEIGHT);
    int half = col_height / 2;
    uint32_t color = col.color;
    color -= ( 5 * col_height);
        for (int j = half; j < HEIGHT - half; ++j) {
            //  printf("here\n");
            uint32_t* pixels = (uint32_t*) surface->pixels;
                pixels[j * surface->w + i] = color;
        }
  //  }
    SDL_UpdateWindowSurface(wind);
    SDL_UnlockSurface(surface);
}*/

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
    DRAW_COL col = RVECTOR_cast_seek_length(turn_vec, map, map_width);


    int thiscolor;
    if (col.distance > 30 && col.distance < 40) {
        thiscolor = 0xFFFFFFFF;
    }
    else if (col.distance > 40 && col.distance < 50) {

                thiscolor = 0xDDDDDDDD;
    }
    else if (col.distance > 50 && col.distance < 60) {
        thiscolor = 0xBBBBBBBB;
    }
        else if (col.distance > 60 && col.distance < 70) {

                thiscolor = 0x999999999;
    }
        else if (col.distance > 70 && col.distance < 80) {

                thiscolor = 0x66666666;
    }
    else {
        thiscolor = 0x33333333;
    }

        int col_height = HEIGHT - (int) (( col.distance / (double) MAP_HEIGHT) * (double) HEIGHT);
    int half = col_height / 2;

        for (int j = half; j < HEIGHT - half; ++j) {
            //  printf("here\n");
            uint32_t* pixels = (uint32_t*) surface->pixels;
                pixels[j * surface->w + i] = thiscolor;
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


    uint32_t map[9] = { 0x00000099, 0x00000099, 0x00000099,
                    0x00000099, 0x00000000, 0x00000099,
                    0x00000099, 0x00000099, 0x00000099};

    SDL_Surface* surface = SDL_GetWindowSurface(wind);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
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
        GAME_render_view(wind, surface, player, map, 3);
       // SDL_LockSurface(surface);
      //  SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);
     //   SDL_UnlockSurface(surface);
       // SDL_UpdateWindowSurface(wind);
        SDL_Delay(1000 / FPS);
    }
}

