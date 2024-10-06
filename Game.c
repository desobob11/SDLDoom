#include "Game.h"
#include "Const.h"

void GAME_render_view(SDL_Window *wind, SDL_Surface *surface, SDL_Renderer *rend, PLAYER *player, uint32_t *map, int map_width)
{

  SDL_LockSurface(surface);
  SDL_memset(surface->pixels, 0x00000000, surface->h * surface->pitch);

  RVECTOR h_iter;
  double x_incr = player->horizon.head.x - player->horizon.tail.x;
  double z_incr = player->horizon.head.z - player->horizon.tail.z;
  x_incr /= RVECTOR_length(player->horizon);
  z_incr /= RVECTOR_length(player->horizon);
  x_incr /= 16;
  z_incr /= 16;
  RVERTEX h_head = player->horizon.tail;
  h_iter.head = h_head;
  h_iter.tail = h_head;

  for (int i = 0; i < 800; i += 1)
  {

    RVERTEX plane_point = h_iter.head;
    RVECTOR ray;
    ray.head = plane_point;
    ray.tail = player->position.head;
    double ray_x_incr = ray.head.x - ray.tail.x;
    double ray_z_incr = ray.head.z - ray.tail.z;
    ray_x_incr /= RVECTOR_length(ray);
    ray_z_incr /= RVECTOR_length(ray);
    ray.head = ray.tail;
    ray.head.x += ray_x_incr;
    ray.head.z += ray_z_incr;

    DRAW_COL col = RVECTOR_cast_seek_length(rend, ray, player->horizon, map, map_width);


        int col_height = SCREEN_HEIGHT - (SCREEN_HEIGHT / (( (col.distance)) / 100.0));
        printf("%d\n", col_height);
       // col_height *= 20;
        int half = col_height / 2;
        for (int k = i; k < i + 1; ++k)
        { 
          for (int j = half; j < SCREEN_HEIGHT - half; ++j) {
              uint32_t* pixels = (uint32_t*) surface->pixels;
                  pixels[j * surface->w + k] = col.color;
        
          }

      
      }
      h_iter.head.x += x_incr * 1;
      h_iter.head.z += z_incr * 1;
    }
    SDL_UpdateWindowSurface(wind);
    SDL_UnlockSurface(surface);
}