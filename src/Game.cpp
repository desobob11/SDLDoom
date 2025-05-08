#include "Game.h"

#include "Const.h"

int RENDER_MODE = 0;
void GAME_render_view(SDL_Window *wind, SDL_Surface *surface,
                      SDL_Renderer *rend, PLAYER *player, uint32_t *map,
                      int map_w, int map_h) {
    SDL_LockSurface(surface);
    SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);

    DOOM::Vector h_iter{};
    double x_incr = player->horizon.head.x - player->horizon.tail.x;
    double z_incr = player->horizon.head.z - player->horizon.tail.z;
    x_incr /= player->horizon.Vector_length();
    z_incr /= player->horizon.Vector_length();
    ;
    x_incr /= 16;
    z_incr /= 16;
    DOOM::VERTEX h_head = player->horizon.tail;
    h_iter.head = h_head;
    h_iter.tail = h_head;

    for (int i = 0; i < 800; i += 1) {
        DOOM::VERTEX plane_point = h_iter.head;
        DOOM::Vector ray;
        ray.head = plane_point;
        ray.tail = player->position.head;
        double ray_x_incr = ray.head.x - ray.tail.x;
        double ray_z_incr = ray.head.z - ray.tail.z;
        ray_x_incr /= ray.Vector_length();
        ray_z_incr /= ray.Vector_length();
        ray.head = ray.tail;
        ray.head.x += ray_x_incr;
        ray.head.z += ray_z_incr;

        DOOM::DRAW_COL col = ray.Vector_cast_seek_length(rend, player->horizon,
                                                         map, map_w, map_h);

        int col_height =
            SCREEN_HEIGHT - (SCREEN_HEIGHT / (((col.distance)) / 100.0));

        // draw entire column that color
        if (col_height < 0) {
            for (int k = i; k < i + 1; ++k) {
                for (int j = 0; j < SCREEN_HEIGHT; ++j) {
                    uint32_t *pixels = (uint32_t *)surface->pixels;
                    pixels[j * surface->w + k] = col.color;
                }
            }
        } else {
            // col_height *= 20;
            int half = col_height / 2;
            for (int k = i; k < i + 1; ++k) {
                for (int j = half; j < SCREEN_HEIGHT - half; ++j) {
                    uint32_t *pixels = (uint32_t *)surface->pixels;
                    pixels[j * surface->w + k] = col.color;
                }
            }
        }

        h_iter.head.x += x_incr;
        h_iter.head.z += z_incr;
    }
    SDL_UnlockSurface(surface);
}