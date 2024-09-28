#ifndef PLAYER_H_
#define PLAYER_H_

#include "SDL2/include/SDL2/SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "RVector.h"


typedef struct PLAYER {
    RVECTOR position;

} PLAYER;

void move_player(PLAYER *player, SDL_Event event, int l_width, int l_height);
RVECTOR read_pos(PLAYER* player);


#endif