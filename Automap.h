#ifndef AUTOMAP_H_
#define AUTOMAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Wall.h"
#include "RVector.h"
#include "Player.h"


typedef struct MAP {
    int h;
    int w;
    double v_h;
    double v_w;
    WALL* map;
} MAP;

extern MAP current_map;


void AUTOMAP_render_map(SDL_Window *wind, SDL_Surface *surface, WALL* map, RVECTOR player_pos);

#endif