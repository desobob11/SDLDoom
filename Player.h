#ifndef PLAYER_H_
#define PLAYER_H_

#include "SDL2/include/SDL2/SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "RVector.h"


#define MOUSE_SENS 50.0

typedef struct PLAYER {
    RVECTOR position;
    RVECTOR dir_vector;
    double direction;
    RVECTOR horizon;
} PLAYER;

void PLAYER_move_player(PLAYER *player, SDL_Event event, uint32_t* map, int l_width, int l_height);
RVECTOR read_pos(PLAYER* player);

PLAYER *PLAYER_init_player(RVERTEX head);
void PLAYER_rotate_camera(PLAYER *player, SDL_Event event);

#endif