#include "Automap.h"





void AUTOMAP_render_map(SDL_Window* wind, SDL_Surface* surface, MAP map, RVECTOR player_pos) {
    WALL* walls = map.map;
    SDL_LockSurface(surface);
    SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);


    AUTOMAP_render_player(surface, player_pos);
    AUTOMAP_render_walls(surface, walls, map.h * map.w, player_pos);


   // SDL_UpdateWindowSurface(wind);
    SDL_UnlockSurface(surface);
}

void AUTOMAP_render_player(SDL_Surface* surface, RVECTOR player_pos) {
    SDL_LockSurface(surface);
    uint32_t* pixels = (uint32_t*) surface->pixels;
    uint32_t x_off = AUTOMAP_get_draw_offset_x(player_pos);
    uint32_t z_off = AUTOMAP_get_draw_offset_z(player_pos);


    printf("%d %d\n", x_off, z_off);


    for (int i = z_off; i < z_off + PLAYER_DOT_H; ++i) {
        for (int j = z_off; j < x_off + PLAYER_DOT_W; ++j) {
            pixels[i* SCREEN_WIDTH + j] = PLAYER_DRAW_COLOR;
        }
    }
    SDL_UnlockSurface(surface);
}


void AUTOMAP_render_wall(SDL_Surface* surface, WALL wall, RVECTOR player_pos) {
    uint32_t* pixels = surface->pixels;
    uint32_t x_off = wall.x_pos - player_pos.head.x;// - AUTOMAP_get_draw_offset_x(player_pos);
    uint32_t z_off = wall.z_pos - player_pos.head.z;// - AUTOMAP_get_draw_offset_z(player_pos);

    SDL_LockSurface(surface);
    for (int i = z_off; i < z_off + BLOCK_SIZE; ++i) {
        for (int j = x_off; j < x_off + BLOCK_SIZE; ++j) {
            if (i >= 0 && i < SCREEN_HEIGHT && j >= 0 && j < SCREEN_WIDTH) {
                pixels[i * SCREEN_WIDTH + j] = wall.color;
            }
        }
    }
    SDL_UnlockSurface(surface);



}

void AUTOMAP_render_walls(SDL_Surface* surface, WALL* walls, int walls_len, RVECTOR player_pos) {
    for (int i = 0; i < walls_len; ++i) {
        AUTOMAP_render_wall(surface, walls[i], player_pos);
    }
}

uint32_t AUTOMAP_get_draw_offset_x(RVECTOR player_pos) {
    return player_pos.head.x - (player_pos.head.x - (SCREEN_WIDTH / 2) - (PLAYER_DOT_W / 2));
}

uint32_t AUTOMAP_get_draw_offset_z(RVECTOR player_pos) {
    return player_pos.head.z - (player_pos.head.z - (SCREEN_HEIGHT / 2) - (PLAYER_DOT_H / 2));
}
