#ifndef AUTOMAP_H_
#define AUTOMAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Player.h"



typedef struct MAP {
    int h;
    int w;
    double v_h;
    double v_w;
    uint32_t* map;
} MAP;

extern MAP current_map;

uint32_t* AUTOMAP_create_map(MAP amap, uint32_t* arr);


void AUTOMAP_render_map(uint32_t map, PLAYER* player);














#endif