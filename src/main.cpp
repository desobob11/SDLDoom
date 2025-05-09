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
#include "LevelState.h"

#define SDL_HINT_RENDER_VSYNC "SDL_RENDER_VSYNC"

#define SPEED 600
#define FPS 120

#define MAP_HEIGHT (BLOCK_SIZE * 7)
#define MAP_WIDTH (BLOCK_SIZE * 7)

extern int DRAW_MODE;
int DRAW_MODE = 0;

int main(int argc, char* argv[]) {


    /* Initializes the timer, audio, video, joystick,
    haptic, gamecontroller and events subsystems */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }
    /* Create a window */
    SDL_Window* wind = SDL_CreateWindow("SDoomL", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, 0);
    if (!wind) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(wind);
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
    if (!surface) {
        printf("Error creating surface: %s\n", SDL_GetError());
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return 0;
    }

    if (SDL_SetRelativeMouseMode(SDL_TRUE)) {
        printf("Error capturing mouse: %s\n", SDL_GetError());
    }

    if (SDL_ShowCursor(SDL_DISABLE)) {
        printf("Error hiding cursor: %s\n", SDL_GetError());
    }

    NGIN::WALL red = {0x00FF0000};
    NGIN::WALL green = {0x0000FF00};
    NGIN::WALL blue = {0x000000FF};
    NGIN::WALL yellow = {0x00FFFF00};
    NGIN::WALL white = {0x00FFFFFF};
    NGIN::WALL none = {0x00000000};

    DOOM::VERTEX start_pos = {700, 0, 700};
    PLAYER* player = PLAYER_init_player(start_pos);

    MAP map;
    NGIN::Sprite* sprites[49] = {
        nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr,
        nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr, nullptr, 
        nullptr, nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, 
        nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr, 
        nullptr,  nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
        nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, 
        nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr, nullptr};

    NGIN::WALL walls[49] = {
        white, white, white, white,  white, white, white, 
        white, none,  none, none,  none,  blue,  white,  
        white, none,  red,   none,  none,  none, white, 
        white, none,  none,   none,  none,  none,  white, 
        white, none, red,   none,  none,  yellow, white, 
        white, green, none,  none,  none, none,  white, 
        white, white,  white, white, white, white, white};
    map.map = walls;

    NGIN::LevelState level {walls, sprites};
    NGIN::Sprite sp1 {"imp", DOOM::VERTEX {300.0, 0, 300.0}};

    level.batch.addSprite(&sp1);
    level.batch.loadImages();

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            walls[i * 7 + j].x_pos = (j * BLOCK_SIZE);
            walls[i * 7 + j].z_pos = (i * BLOCK_SIZE);
        }
    }

    map.w = 7;
    map.h = 7;

    uint32_t wall_colors[49];
    for (int i = 0; i < 49; ++i) {
        wall_colors[i] = walls[i].color;
    }

    map.v_h = map.h * BLOCK_SIZE;
    map.v_w = map.w * BLOCK_SIZE;

    SDL_Event event;
    while (true) {
        SDL_UpdateWindowSurface(wind);
        /* Process events */
        while (SDL_PollEvent(&event)) {
            // PLAYER_move_player(player, event, map.map, 7, 7);
            // PLAYER_rotate_camera(player, event);

            if (event.type == SDL_KEYDOWN) {
                SDL_Scancode code = event.key.keysym.scancode;

                if (code == SDL_SCANCODE_TAB) {
                    RENDER_MODE = !RENDER_MODE;
                }
            }

            if (event.type == SDL_QUIT) {
                SDL_Quit();
                SDL_DestroyWindowSurface(wind);
                SDL_DestroyWindow(wind);
                return 0;
            }
        }


        PLAYER_move_player(player, event, wall_colors, map.v_w, map.v_h, map.w,
                           map.h);
        PLAYER_rotate_camera(player, event);
        if (RENDER_MODE == 0) {
            GAME_render_view(wind, surface, NULL, player, level, map.w,
                             map.h);
        } else {
            AUTOMAP_render_map(wind, surface, map, player->position);
        }

        level.batch.updateSpriteDistances(player->position);
        SDL_LockSurface(surface);
       // SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);
        level.batch.renderSprites(surface);
        SDL_UnlockSurface(surface);
        SDL_Delay(1000 / FPS);
    }
}
