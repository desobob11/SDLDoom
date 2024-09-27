#include "Wall.h"
#include <stdio.h>

void WALL_render(WALL wall, SDL_Surface* surface) {

    

    SDL_LockSurface(surface);
    for (int i = wall.x; i < wall.x + wall.w; ++i) {
        for (int j = wall.y; j < wall.y + wall.h; ++j) {
 
            uint32_t* pixels = (uint32_t*) surface->pixels;
            pixels[j * surface->w + i] = wall.color;
            // uint32_t* pixel = (uint32_t* ) ((uint8_t* ) surface->pixels
            //  + (wall.y + j) * surface->pitch + (wall.x * i) * surface->format->BitsPerPixel);

            //if (*pixel != wall.color) {
          //      *pixel = wall.color;
          //  }
        }
    }
    SDL_UnlockSurface(surface);
}
