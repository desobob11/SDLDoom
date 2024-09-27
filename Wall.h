#ifndef WALL_H_
#define WALL_H_
#include "SDL2/include/SDL2/SDL.h"
typedef struct WALL
{
    uint32_t x;
    uint32_t y;
    uint32_t h;
    uint32_t w;
    uint32_t color;
} WALL;



void WALL_render(WALL wall, SDL_Surface* rend);

#endif
