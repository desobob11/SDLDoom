#include "Wall.h"
#include <stdio.h>

void WALL_render(WALL wall, SDL_Surface* surface) {
    uint32_t* pixels = (uint32_t*) surface->pixels;
    

    SDL_LockSurface(surface);
    for (int i = wall.x; i < wall.x + wall.w; ++i) {
        for (int j = wall.y; j < wall.y + wall.h; ++j) {
            uint32_t offset = j * surface->w + i;
            if (offset < surface->w * surface->h)
                pixels[offset] = wall.color;
        }
    }
    SDL_UnlockSurface(surface);
}
