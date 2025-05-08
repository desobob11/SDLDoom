#ifndef AUTOMAP_H_
#define AUTOMAP_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "Const.h"
#include "Player.h"
#include "Vector.h"
#include "LevelState.h"

#define PLAYER_DOT_W 10
#define PLAYER_DOT_H 10
#define PLAYER_DRAW_COLOR 0xFFFF0000

typedef struct MAP {
    int h;
    int w;
    double v_h;
    double v_w;
    WALL* map;
} MAP;

void AUTOMAP_render_map(SDL_Window* wind, SDL_Surface* surface, MAP map,
                        DOOM::Vector player_pos);

void AUTOMAP_render_wall(SDL_Surface* surface, WALL wall,
                         DOOM::Vector player_pos);
void AUTOMAP_render_walls(SDL_Surface* surface, WALL* wall, int walls_len,
                          DOOM::Vector player_pos);
void AUTOMAP_render_player(SDL_Surface* surface, DOOM::Vector player_pos);

void AUTOMAP_render_vector(SDL_Surface* surface, DOOM::Vector vector);

uint32_t AUTOMAP_get_draw_offset_x(DOOM::Vector player_pos);
uint32_t AUTOMAP_get_draw_offset_z(DOOM::Vector player_pos);

#endif