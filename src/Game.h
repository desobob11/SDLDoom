#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <stdlib.h>

#include "../SDL2/include/SDL2/SDL.h"
#include "Player.h"
#include "Vector.h"
#include "LevelState.h"

extern int RENDER_MODE;

namespace NGIN {


typedef struct DRAW_COL {
    uint32_t color;
    double distance;
    double spriteDistance = INT_MAX;
} DRAW_COL;


void GAME_render_view(SDL_Window *wind, SDL_Surface *surface,
                      SDL_Renderer *rend, PLAYER *player, NGIN::LevelState& ls,
                      int map_w, int map_h);

DRAW_COL Vector_cast_seek_length(DOOM::Vector ray, SDL_Renderer* rend, DOOM::Vector h_point, NGIN::LevelState ls, int map_w,
    int map_h, uint32_t pixelCol);
}

#endif