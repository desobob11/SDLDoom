#include "Automap.h"





void AUTOMAP_render_map(SDL_Window* wind, SDL_Surface* surface, MAP map, DOOM::Vector player_pos) {
    SDL_LockSurface(surface);
    SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);


    AUTOMAP_render_player(surface, player_pos);
    AUTOMAP_render_walls(surface, map.map, map.h * map.w, player_pos);
    //AUTOMAP_render_vector(surface, player_pos);

   // SDL_UpdateWindowSurface(wind);
    SDL_UnlockSurface(surface);
}

void AUTOMAP_render_player(SDL_Surface* surface, DOOM::Vector player_pos) {
    SDL_LockSurface(surface);
    uint32_t* pixels = (uint32_t*) surface->pixels;
    uint32_t x_off = AUTOMAP_get_draw_offset_x(player_pos);
    uint32_t z_off = AUTOMAP_get_draw_offset_z(player_pos);



    for (uint32_t i = z_off; i < z_off + PLAYER_DOT_H; ++i) {
        for (uint32_t j = z_off; j < x_off + PLAYER_DOT_W; ++j) {
            pixels[i* SCREEN_WIDTH + j] = PLAYER_DRAW_COLOR;
        }
    }
    SDL_UnlockSurface(surface);
}


void AUTOMAP_render_wall(SDL_Surface* surface, WALL wall, DOOM::Vector player_pos) {
    uint32_t* pixels = static_cast<uint32_t*>(surface->pixels);
    uint32_t x_off = wall.x_pos - player_pos.head.x;// - AUTOMAP_get_draw_offset_x(player_pos);
    uint32_t z_off = wall.z_pos - player_pos.head.z;// - AUTOMAP_get_draw_offset_z(player_pos);

    SDL_LockSurface(surface);
    for (uint32_t i = z_off; i < z_off + BLOCK_SIZE; ++i) {
        for (uint32_t j = x_off; j < x_off + BLOCK_SIZE; ++j) {
            if (i >= 0 && i < SCREEN_HEIGHT && j >= 0 && j < SCREEN_WIDTH) {
                pixels[i * SCREEN_WIDTH + j] = wall.color;
            }
        }
    }
    SDL_UnlockSurface(surface);
}

void AUTOMAP_render_vector(SDL_Surface* surface, DOOM::Vector vector) {
    SDL_LockSurface(surface);

    double vec_length = vect;
    double x_iter = (vector.head.x - vector.tail.x) / vec_length;
    double z_iter = (vector.head.z - vector.tail.z) / vec_length;
    uint32_t* pixels = static_cast<uint32_t*> (surface->pixels);
    DOOM::Vector iter = {vector.tail, vector.tail};

    for (int i = 0; i < vec_length; ++i) {
        uint32_t x_draw = (uint32_t) iter.head.x;
        uint32_t z_draw = (uint32_t) iter.head.z;
        if (x_draw >= 0 && z_draw >= 0 && x_draw < SCREEN_WIDTH && z_draw < SCREEN_HEIGHT) {
            pixels[z_draw * SCREEN_WIDTH + x_draw] = 0x00000AA00;
        }
        iter.head.x += x_iter;
        iter.head.z += z_iter;
    }


    SDL_UnlockSurface(surface);
}

void AUTOMAP_render_walls(SDL_Surface* surface, WALL* walls, int walls_len, DOOM::Vector player_pos) {
    for (int i = 0; i < walls_len; ++i) {
        AUTOMAP_render_wall(surface, walls[i], player_pos);
    }
}

uint32_t AUTOMAP_get_draw_offset_x(DOOM::Vector player_pos) {
    return player_pos.head.x - (player_pos.head.x - (SCREEN_WIDTH / 2) - (PLAYER_DOT_W / 2));
}

uint32_t AUTOMAP_get_draw_offset_z(DOOM::Vector player_pos) {
    return player_pos.head.z - (player_pos.head.z - (SCREEN_HEIGHT / 2) - (PLAYER_DOT_H / 2));
}
