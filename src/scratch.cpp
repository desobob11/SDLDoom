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
#include "Sprite.h"
#include "SpriteBatch.h"
#include "Vector.h"
#include "LevelState.h"

#define SDL_HINT_RENDER_VSYNC "SDL_RENDER_VSYNC"

#define SPEED 600
#define FPS 180

#define MAP_HEIGHT (BLOCK_SIZE * 7)
#define MAP_WIDTH (BLOCK_SIZE * 7)

extern int DRAW_MODE;
int DRAW_MODE = 0;

using namespace std;

int main(int argc, char* argv[]) {
    NGIN::SpriteBatch batch{};

    for (auto iter = batch.lookupTable.begin(); iter != batch.lookupTable.end();
         ++iter) {
        cout << iter->first << " " << iter->second.first << " "
             << iter->second.second << endl;
    }
    NGIN::Sprite sp1{"imp", 0, 0, NGIN::SPRITE_SCALE_BASE};

    batch.addSprite(&sp1);
    batch.loadImages();

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

  //  if (SDL_SetRelativeMouseMode(SDL_TRUE)) {
  //     printf("Error capturing mouse: %s\n", SDL_GetError());
  //  }

   // if (SDL_ShowCursor(SDL_DISABLE)) {
   //     printf("Error hiding cursor: %s\n", SDL_GetError());
   // }

    SDL_Event event;
    while (true) {
        SDL_UpdateWindowSurface(wind);
      //  cout << NGIN::SPRITE_SCALES[sp1.scale] << endl;
        /* Process events */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                SDL_Scancode code = event.key.keysym.scancode;

                if (code == SDL_SCANCODE_DOWN) {
                    sp1.scale = std::max(NGIN::SPRITE_SCALE_MIN, sp1.scale - 1);
                }
                if (code == SDL_SCANCODE_UP) {
                    sp1.scale = std::min(NGIN::SPRITE_SCALE_MAX, sp1.scale + 1);
                }
            }

            if (event.type == SDL_QUIT) {
                SDL_Quit();
                SDL_DestroyWindowSurface(wind);
                SDL_DestroyWindow(wind);
                return 0;
            }
        }

        SDL_LockSurface(surface);
        SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);
        batch.renderSprites(surface);
        SDL_UnlockSurface(surface);
        SDL_Delay(1000 / FPS);
    }
}
