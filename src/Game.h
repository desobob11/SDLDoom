#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <stdlib.h>

#include "../SDL2/include/SDL2/SDL.h"
#include "Player.h"
#include "Vector.h"
#include "LevelState.h"

extern int RENDER_MODE;

void GAME_render_view(SDL_Window *wind, SDL_Surface *surface,
                      SDL_Renderer *rend, PLAYER *player, NGIN::LevelState ls,
                      int map_w, int map_h);

#endif