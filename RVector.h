#ifndef RVECTOR_H_
#define RVECTOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "SDL2/include/SDL2/SDL.h"
#include "Wall.h"



typedef struct DRAW_COL {
    uint32_t color;
    double distance;
} DRAW_COL;

typedef struct RVERTEX {
    double x;
    double y;
    double z;
} RVERTEX;

typedef struct RVECTOR
{
    RVERTEX head;
    RVERTEX tail;
} RVECTOR;
uint32_t GAME_max(uint32_t x, uint32_t y);
RVECTOR RVECTOR_normalize(RVECTOR v);
RVECTOR RVECTOR_diff(RVECTOR v1, RVECTOR v2);
void RVECTOR_print(RVECTOR v);
RVECTOR RVECTOR_cast(RVECTOR v1, RVECTOR v2);
double RVECTOR_length(RVECTOR v);
int RVECTOR_draw_height(double length);
DRAW_COL RVECTOR_cast_seek_length(SDL_Renderer* rend, RVECTOR v1, RVECTOR h_point, WALL* walls, int map_w, int map_h);
uint32_t RVECTOR_darken_color(uint32_t color, uint32_t distance);
RVERTEX RVECTOR_closest_point(RVERTEX ray_head, RVECTOR horizon);

#endif
