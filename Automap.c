#include "Automap.h"





void AUTOMAP_render_map(SDL_Window* wind, SDL_Surface* surface, WALL* map, RVECTOR player_pos) {

    SDL_LockSurface(surface);
    SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);





   // SDL_UpdateWindowSurface(wind);
    SDL_UnlockSurface(surface);
}


void AUTOMAP_render_wall(SDL_Surface* surface, WALL wall) {




}
