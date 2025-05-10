#include "Game.h"

#include <set>

#include "Const.h"
#include <algorithm>

int RENDER_MODE = 0;

namespace NGIN {

void GAME_render_view(SDL_Window *wind, SDL_Surface *surface,
                      SDL_Renderer *rend, PLAYER *player, NGIN::LevelState &ls,
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

    DRAW_COL *cols = new DRAW_COL[SCREEN_WIDTH];

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

        cols[i] = Vector_cast_seek_length(ray, rend, player->horizon, ls, map_w,
                                          map_h, i);

        h_iter.head.x += x_incr;
        h_iter.head.z += z_incr;
    }

    // render sprites first
    ls.batch.renderSprites(surface);

    for (int i = 0; i < 800; i += 1) {
        DRAW_COL col = cols[i];

        // draw entire column that color
        int col_height =
            SCREEN_HEIGHT - (SCREEN_HEIGHT / (((col.distance)) / 100.0));


        if (col_height < 0) {
            for (int k = i; k < i + 1; ++k) {
                for (int j = 0; j < SCREEN_HEIGHT; ++j) {
                    uint32_t *pixels = (uint32_t *)surface->pixels;
                    if (col.distance < col.spriteDistance || pixels[j * surface->w + k] == 0x00000000) {
                        pixels[j * surface->w + k] = col.color;
                    }
                }
            }
        } else {
            // col_height *= 20;
            int half = col_height / 2;
            for (int k = i; k < i + 1; ++k) {
                for (int j = half; j < SCREEN_HEIGHT - half; ++j) {
                    uint32_t *pixels = (uint32_t *)surface->pixels;
                    if (col.distance < col.spriteDistance || pixels[j * surface->w + k] == 0x00000000) {
                        pixels[j * surface->w + k] = col.color;
                    }
                }
            }
        }
    }
    SDL_UnlockSurface(surface);
}

DRAW_COL Vector_cast_seek_length(DOOM::Vector ray, SDL_Renderer *rend,
                                 DOOM::Vector h_point, NGIN::LevelState ls,
                                 int map_w, int map_h, uint32_t pixelCol) {
    std::set<NGIN::Sprite *> renderedSprites{};
    int hit = 0;
    DOOM::Vector copy = DOOM::Vector{ray.head, ray.tail};
    DRAW_COL col;

    double x_incr = ray.head.x - ray.tail.x;
    double z_incr = ray.head.z - ray.tail.z;

    int i = 0;
    int j = 0;
    while (!hit && (i >= 0 && i < map_h && j >= 0 && j < map_w)) {
        i = (int)copy.head.z / BLOCK_SIZE;
        j = (int)copy.head.x / BLOCK_SIZE;
        // keep going until I find a wall
        if (ls.wallColors[i * map_w + j]) {
            copy.tail = DOOM::Vector::Vector_closest_point(copy.head, h_point);

            col.distance = copy.Vector_length();
            col.color = DOOM::Vector::Vector_darken_color(
                ls.wallColors[i * map_w + j], (uint32_t)col.distance);
            hit = 1;
        }

        // we have a sprite somewhere on this block
        if (ls.sprites[i * map_w + j]) {
            NGIN::Sprite *rendering = ls.sprites[i * map_w + j];
            DOOM::VERTEX *hb = rendering->getHitBox();
            
          //  for (size_t i = 0; i < 4; ++i) {
          //      std::cout << hb[i] << " ";
        //    }
          //  std::cout << std::endl;

       //   std::cout << copy.head << std::endl;

            // this ray is overlapping with the sprite's world coord
            if (copy.overlapsBox(hb[0], hb[1], hb[2], hb[3])) {
                if (renderedSprites.find(rendering) == renderedSprites.end()) {
                    renderedSprites.insert(rendering);
                  //  uint32_t startDrawCol = std::max(pixelCol - rene)

                    // TODO
                    // wow needs to be an easier way to get this info
                    uint32_t baseWidth = SpriteBatch::lookupTable[rendering->name].second;
                    uint32_t scaledWidth = static_cast<uint32_t>(baseWidth * NGIN::SPRITE_SCALES[rendering->scale]);
                    rendering->columnStart = std::max(pixelCol - scaledWidth / 2, static_cast<uint32_t>(0));
                    col.spriteDistance = static_cast<float>(rendering->dist);
                }
            }
            delete hb;
        }

        if (!hit) {
            DOOM::VERTEX new_head = {copy.head.x + x_incr, 0,
                                     copy.head.z + z_incr};
            copy.head = new_head;
        }
    }

    return col;
}
}  // namespace NGIN