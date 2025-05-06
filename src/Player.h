#ifndef PLAYER_H_
#define PLAYER_H_

#include "../SDL2/include/SDL2/SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Vector.h"

#include "Wall.h"


#define MOUSE_SENS 300.0

#define KEY_SENS 50.0

typedef struct PLAYER {
    DOOM::Vector position;
    DOOM::Vector dir_vector;
    double direction;
    DOOM::Vector horizon;
} PLAYER;

void PLAYER_move_player(PLAYER *player, SDL_Event event, uint32_t* map, int map_vw,
int map_vh, int map_w, int map_h);
DOOM::Vector read_pos(PLAYER* player);

PLAYER *PLAYER_init_player(DOOM::VERTEX head);
void PLAYER_rotate_camera(PLAYER *player, SDL_Event event);

#endif