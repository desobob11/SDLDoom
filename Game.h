#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <stdlib.h>
#include "SDL2/include/SDL2/SDL.h"
#include "Player.h"


void GAME_render_view(SDL_Window* wind, SDL_Surface* surface, 
SDL_Renderer* rend, PLAYER* player, uint32_t* map, int map_width);





#endif