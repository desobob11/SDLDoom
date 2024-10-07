#include "Player.h"
#include <math.h>
#include "Const.h"
#include "Automap.h"    // this is bad




#define HORIZON_DIST 25
#define MOVE_SPEED 5.0

#define HORIZ_LEN 25
void PLAYER_move_player(PLAYER *player, SDL_Event event, uint32_t* map, int l_width, int l_height)
{   int i = 0, j = 0;
    if (event.type == SDL_KEYDOWN)
    {
        double x_incr = (player->dir_vector.head.x - player->dir_vector.tail.x)  * MOVE_SPEED;
        double z_incr = (player->dir_vector.head.z - player->dir_vector.tail.z) * MOVE_SPEED;

        RVERTEX new_dir_ahead = {player->position.head.x + x_incr,0, player->position.head.z + z_incr};
        RVERTEX new_dir_back = {player->position.head.x - x_incr,0, player->position.head.z - z_incr};
        SDL_Scancode code = event.key.keysym.scancode;


    // TODO: correct magic numbers and definitions of level dimensions
        int check_ahead = new_dir_ahead.z - HORIZON_DIST  < current_map.v_h && new_dir_ahead.x - HORIZON_DIST < current_map.v_w
            && new_dir_ahead.z - HORIZON_DIST >= 0 && new_dir_ahead.x - HORIZON_DIST >= 0;
        int check_back = new_dir_back.z < current_map.v_h && new_dir_back.x < current_map.v_w
            && new_dir_back.z >= 0 && new_dir_back.x >= 0;


        if (code == SDL_SCANCODE_W)
        {
                i = (int) new_dir_ahead.z / BLOCK_SIZE;
                j = (int) new_dir_ahead.x / BLOCK_SIZE;
                if (i >= 0 && i < current_map.h && j >= 0 && j < current_map.w) {
                
                        if (check_ahead) {
                            if (*(current_map.map + ((i * l_width) + j)) == 0) {
                                player->dir_vector.tail.x += x_incr;
                                player->dir_vector.tail.z += z_incr;

                                player->dir_vector.head.x += x_incr;
                                player->dir_vector.head.z += z_incr;
                                player->position.head = new_dir_ahead;
                            }
                        }
                }
   
        }
        else if (code == SDL_SCANCODE_S)
        {
            i = (int)new_dir_back.z / BLOCK_SIZE;
            j = (int)new_dir_back.x / BLOCK_SIZE;
            if (i >= 0 && i < current_map.h && j >= 0 && j < current_map.w)
            {

                if (check_back)
                {
                    if (*(current_map.map + ((i * l_width) + j)) == 0)
                    {
                        player->dir_vector.tail.x += x_incr * MOVE_SPEED;
                        player->dir_vector.tail.z += z_incr * MOVE_SPEED;

                        player->dir_vector.head.x += x_incr * MOVE_SPEED;
                        player->dir_vector.head.z += z_incr * MOVE_SPEED;
                        player->position.head = new_dir_ahead;
                    }
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
{   
    if (event.type == SDL_KEYDOWN)
    {
        SDL_Scancode code = event.key.keysym.scancode;
        if (code == SDL_SCANCODE_LEFT)
            player->direction -= (M_PI / MOUSE_SENS);
        if (code == SDL_SCANCODE_RIGHT)
            player->direction += (M_PI / MOUSE_SENS);

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
}

