#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
#include <math.h>

#include "../SDL2/include/SDL2/SDL.h"
#include "Automap.h"
#include "Const.h"
#include "Game.h"
#include "Player.h"
#include "Vector.h"
#include "Wall.h"
#include "Sprite.h"

#define SDL_HINT_RENDER_VSYNC "SDL_RENDER_VSYNC"

#define SPEED 600
#define FPS 120

#define MAP_HEIGHT (BLOCK_SIZE * 7)
#define MAP_WIDTH (BLOCK_SIZE * 7)

extern int DRAW_MODE;
int DRAW_MODE = 0;

int main(int argc, char* argv[]) {
    
}
