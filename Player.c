#include "Player.h"
#include <math.h>
#include "Const.h"
#include "Wall.h"
#include "Automap.h"





#define HORIZON_DIST 25
#define MOVE_SPEED 10.0

#define HORIZ_LEN 25
void PLAYER_move_player(PLAYER *player, SDL_Event event, uint32_t* walls, int map_vw, int map_vh, int map_w, int map_h)
{   int i = 0, j = 0;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    double x_incr = (player->dir_vector.head.x - player->dir_vector.tail.x) * MOVE_SPEED;
    double z_incr = (player->dir_vector.head.z - player->dir_vector.tail.z) * MOVE_SPEED;

    if (keystates[SDL_SCANCODE_LSHIFT]) {
        x_incr /= 2;
        z_incr /= 2;
    }


    RVERTEX new_dir_ahead = {player->position.head.x + x_incr,0, player->position.head.z + z_incr};
    RVERTEX new_dir_back = {player->position.head.x - x_incr,0, player->position.head.z - z_incr};
    RVERTEX new_dir_left = {player->position.head.x - x_incr, 0, player->position.head.z - z_incr};
    RVERTEX new_dir_right = {player->position.head.x - x_incr, 0, player->position.head.z - z_incr};
    // TODO: correct magic numbers and definitions of level dimensions
    int check_ahead = new_dir_ahead.z - HORIZON_DIST  < map_vh && new_dir_ahead.x - HORIZON_DIST < map_vw
        && new_dir_ahead.z - HORIZON_DIST >= 0 && new_dir_ahead.x - HORIZON_DIST >= 0;

    int check_back = new_dir_back.z - HORIZON_DIST  < map_vh && new_dir_back.x - HORIZON_DIST < map_vw
        && new_dir_back.z - HORIZON_DIST >= 0 && new_dir_back.x - HORIZON_DIST >= 0;

    int check_back = new_dir_back.z - HORIZON_DIST < map_vh && new_dir_back.x - HORIZON_DIST < map_vw && new_dir_back.z - HORIZON_DIST >= 0 && new_dir_back.x - HORIZON_DIST >= 0;

    if (keystates[SDL_SCANCODE_W])
    {
            i = (int) new_dir_ahead.z / BLOCK_SIZE;
            j = (int) new_dir_ahead.x / BLOCK_SIZE;
            if (i >= 0 && i < map_h && j >= 0 && j < map_w) {
            
                    if (check_ahead) {
                        if (walls[i*map_w + j] == 0) {
                            player->dir_vector.tail.x += x_incr;
                            player->dir_vector.tail.z += z_incr;

                            player->dir_vector.head.x += x_incr;
                            player->dir_vector.head.z += z_incr;
                            player->position.head = new_dir_ahead;
                        }
                    }
            }

    }

    else if (keystates[SDL_SCANCODE_S])
    {
        i = (int)new_dir_back.z / BLOCK_SIZE;
        j = (int)new_dir_back.x / BLOCK_SIZE;
        if (i >= 0 && i < map_h && j >= 0 && j < map_w)
        {

            if (check_back)
            {
                if (walls[i * map_w + j] == 0)
                {
                    player->dir_vector.tail.x -= x_incr;
                    player->dir_vector.tail.z -= z_incr;

                    player->dir_vector.head.x -= x_incr;
                    player->dir_vector.head.z -= z_incr;
                    player->position.head = new_dir_back;
                }
            }
        }
    }
}

RVECTOR read_pos(PLAYER *player) {
    return player->position;
}

PLAYER *PLAYER_init_player(RVERTEX head)
{
    PLAYER* player = (PLAYER*) malloc(sizeof(PLAYER));
    RVERTEX tail = {0, 0, 0};
    player->position.head = head;
    player->position.tail = tail;

    player->direction = (3 * M_PI) / 2;

    RVERTEX dir_tail = head;
    RVERTEX dir_head = {head.x + cos(player->direction), 0, head.z - sin(player->direction)};
    RVECTOR dir_vector = {dir_head, dir_tail};
    player->dir_vector = dir_vector;

  RVERTEX horiz_tail = player->dir_vector.head;
    horiz_tail.x += (cos(player->direction) * HORIZON_DIST);
    horiz_tail.z -= (sin(player->direction) * HORIZON_DIST);
    double hor_dir = player->direction + (M_PI / 2.0);
    RVERTEX horiz_head = {horiz_tail.x + (cos(hor_dir) * HORIZ_LEN), 0, horiz_tail.z - (sin(hor_dir) * HORIZ_LEN)};
    RVERTEX h_f_head = horiz_head;


    horiz_tail = player->dir_vector.head;
    horiz_tail.x += (cos(player->direction) * HORIZON_DIST);
    horiz_tail.z -= (sin(player->direction) * HORIZON_DIST);
    hor_dir = player->direction - (M_PI / 2.0);
    horiz_head.x = horiz_tail.x + (cos(hor_dir) * HORIZ_LEN);
    horiz_head.z = horiz_tail.z - (sin(hor_dir) * HORIZ_LEN);
    RVERTEX h_f_tail = horiz_head;
    player->horizon.head = h_f_head;
    player->horizon.tail = h_f_tail;
    return player;
}

void PLAYER_rotate_camera(PLAYER *player, SDL_Event event)
{       const uint8_t* keystates = SDL_GetKeyboardState(NULL);
        int xrel, yrel;

        SDL_GetRelativeMouseState(&xrel, &yrel);
        


        if (xrel != 0)
            player->direction += (xrel / MOUSE_SENS);
            
        if (keystates[SDL_SCANCODE_LEFT])
            player->direction -= (M_PI / KEY_SENS);

        if (keystates[SDL_SCANCODE_RIGHT])
            player->direction += (M_PI / KEY_SENS);

   

        if (player->direction > 2.0 * M_PI) {
            player->direction -= (2.0 * M_PI);
        }
        else if (player->direction < 0)
        {
            player->direction += (2.0 * M_PI);
        }
        RVERTEX dir_head = {player->position.head.x + cos(player->direction), 0, player->position.head.z - sin(player->direction)};
        player->dir_vector.head = dir_head;

    RVERTEX horiz_tail = player->dir_vector.head;
    horiz_tail.x += (cos(player->direction) * HORIZON_DIST);
    horiz_tail.z -= (sin(player->direction) * HORIZON_DIST);
    double hor_dir = player->direction + (M_PI / 2.0);
    RVERTEX horiz_head = {horiz_tail.x + (cos(hor_dir) * HORIZ_LEN), 0, horiz_tail.z - (sin(hor_dir) * HORIZ_LEN)};
    RVERTEX h_f_head = horiz_head;


    horiz_tail = player->dir_vector.head;
    horiz_tail.x += (cos(player->direction) * HORIZON_DIST);
    horiz_tail.z -= (sin(player->direction) * HORIZON_DIST);
    hor_dir = player->direction - (M_PI / 2.0);
    horiz_head.x = horiz_tail.x + (cos(hor_dir) * HORIZ_LEN);
    horiz_head.z = horiz_tail.z - (sin(hor_dir) * HORIZ_LEN);
    RVERTEX h_f_tail = horiz_head;
    player->horizon.head = h_f_head;
    player->horizon.tail = h_f_tail;

     //   RVECTOR_print(player->dir_vector);
     //   printf("%.2lf %.2lf\n", player->direction / M_PI, RVECTOR_length(player->dir_vector));
    
}

