#include "Player.h"

#include <math.h>

#include "Automap.h"
#include "Const.h"
#define HORIZON_DIST 32
#define MOVE_SPEED 10.0

#define HORIZ_LEN 32
void PLAYER_move_player(PLAYER* player, SDL_Event event, uint32_t* walls,
                        int map_vw, int map_vh, int map_w, int map_h) {
    int i = 0, j = 0;
    const uint8_t* keystates = SDL_GetKeyboardState(NULL);

    double x_incr =
        (player->dir_vector.head.x - player->dir_vector.tail.x) * MOVE_SPEED;
    double z_incr =
        (player->dir_vector.head.z - player->dir_vector.tail.z) * MOVE_SPEED;

    DOOM::Vector perp_dir =
        DOOM::Vector::Vector_rotate_vector(M_PI / 2, player->dir_vector);

    double perp_x_incr = (perp_dir.head.x - perp_dir.tail.x) * MOVE_SPEED;
    double perp_z_incr = (perp_dir.head.z - perp_dir.tail.z) * MOVE_SPEED;

    DOOM::VERTEX new_dir_ahead = {player->position.head.x + x_incr, 0,
                                  player->position.head.z + z_incr};
    DOOM::VERTEX new_dir_back = {player->position.head.x - x_incr, 0,
                                 player->position.head.z - z_incr};

    if (keystates[SDL_SCANCODE_LSHIFT]) {
        x_incr /= 2;
        z_incr /= 2;
        perp_x_incr /= 2;
        perp_z_incr /= 2;
    }

    // TODO: correct magic numbers and definitions of level dimensions
    int check_ahead = new_dir_ahead.z - HORIZON_DIST < map_vh &&
                      new_dir_ahead.x - HORIZON_DIST < map_vw &&
                      new_dir_ahead.z - HORIZON_DIST >= 0 &&
                      new_dir_ahead.x - HORIZON_DIST >= 0;

    int check_back = new_dir_back.z - HORIZON_DIST < map_vh &&
                     new_dir_back.x - HORIZON_DIST < map_vw &&
                     new_dir_back.z - HORIZON_DIST >= 0 &&
                     new_dir_back.x - HORIZON_DIST >= 0;

    if (keystates[SDL_SCANCODE_W]) {
        i = (int)new_dir_ahead.z / BLOCK_SIZE;
        j = (int)new_dir_ahead.x / BLOCK_SIZE;
        if (i >= 0 && i < map_h && j >= 0 && j < map_w) {
            if (check_ahead) {
                if (walls[i * map_w + j] == 0) {
                    player->dir_vector.tail.x += x_incr;
                    player->dir_vector.tail.z += z_incr;

                    player->dir_vector.head.x += x_incr;
                    player->dir_vector.head.z += z_incr;
                    player->position.head = new_dir_ahead;
                }
            }
        }

    }

    else if (keystates[SDL_SCANCODE_S]) {
        i = (int)new_dir_back.z / BLOCK_SIZE;
        j = (int)new_dir_back.x / BLOCK_SIZE;
        if (i >= 0 && i < map_h && j >= 0 && j < map_w) {
            if (check_back) {
                if (walls[i * map_w + j] == 0) {
                    player->dir_vector.tail.x -= x_incr;
                    player->dir_vector.tail.z -= z_incr;

                    player->dir_vector.head.x -= x_incr;
                    player->dir_vector.head.z -= z_incr;
                    player->position.head = new_dir_back;
                }
            }
        }
    }

    DOOM::VERTEX new_dir_left = {player->position.head.x + perp_x_incr, 0,
                                 player->position.head.z + perp_z_incr};
    DOOM::VERTEX new_dir_right = {player->position.head.x - perp_x_incr, 0,
                                  player->position.head.z - perp_z_incr};

    int check_left = new_dir_left.z - HORIZON_DIST < map_vh &&
                     new_dir_left.x - HORIZON_DIST < map_vw &&
                     new_dir_left.z - HORIZON_DIST >= 0 &&
                     new_dir_left.x - HORIZON_DIST >= 0;

    int check_right = new_dir_right.z - HORIZON_DIST < map_vh &&
                      new_dir_right.x - HORIZON_DIST < map_vw &&
                      new_dir_right.z - HORIZON_DIST >= 0 &&
                      new_dir_right.x - HORIZON_DIST >= 0;

    if (keystates[SDL_SCANCODE_A]) {
        i = (int)new_dir_left.z / BLOCK_SIZE;
        j = (int)new_dir_left.x / BLOCK_SIZE;
        if (i >= 0 && i < map_h && j >= 0 && j < map_w) {
            if (check_left) {
                if (walls[i * map_w + j] == 0) {
                    player->dir_vector.tail.x += perp_x_incr;
                    player->dir_vector.tail.z += perp_z_incr;

                    player->dir_vector.head.x += perp_x_incr;
                    player->dir_vector.head.z += perp_z_incr;

                    player->position.head = new_dir_left;
                }
            }
        }
    }

    else if (keystates[SDL_SCANCODE_D]) {
        i = (int)new_dir_right.z / BLOCK_SIZE;
        j = (int)new_dir_right.x / BLOCK_SIZE;
        if (i >= 0 && i < map_h && j >= 0 && j < map_w) {
            if (check_right) {
                if (walls[i * map_w + j] == 0) {
                    player->dir_vector.tail.x -= perp_x_incr;
                    player->dir_vector.tail.z -= perp_z_incr;

                    player->dir_vector.head.x -= perp_x_incr;
                    player->dir_vector.head.z -= perp_z_incr;

                    player->position.head = new_dir_right;
                }
            }
        }
    }
}

DOOM::Vector read_pos(PLAYER* player) { return player->position; }

PLAYER* PLAYER_init_player(DOOM::VERTEX head) {
    PLAYER* player = (PLAYER*)malloc(sizeof(PLAYER));
    DOOM::VERTEX tail = {0, 0, 0};
    player->position.head = head;
    player->position.tail = tail;

    player->direction = (3 * M_PI) / 2;

    DOOM::VERTEX dir_tail = head;
    DOOM::VERTEX dir_head = {head.x + cos(player->direction), 0,
                             head.z - sin(player->direction)};
    DOOM::Vector dir_vector = {dir_head, dir_tail};
    player->dir_vector = dir_vector;

    DOOM::VERTEX horiz_tail = player->dir_vector.head;
    horiz_tail.x += (cos(player->direction) * HORIZON_DIST);
    horiz_tail.z -= (sin(player->direction) * HORIZON_DIST);
    double hor_dir = player->direction + (M_PI / 2.0);
    DOOM::VERTEX horiz_head = {horiz_tail.x + (cos(hor_dir) * HORIZ_LEN), 0,
                               horiz_tail.z - (sin(hor_dir) * HORIZ_LEN)};
    DOOM::VERTEX h_f_head = horiz_head;

    horiz_tail = player->dir_vector.head;
    horiz_tail.x += (cos(player->direction) * HORIZON_DIST);
    horiz_tail.z -= (sin(player->direction) * HORIZON_DIST);
    hor_dir = player->direction - (M_PI / 2.0);
    horiz_head.x = horiz_tail.x + (cos(hor_dir) * HORIZ_LEN);
    horiz_head.z = horiz_tail.z - (sin(hor_dir) * HORIZ_LEN);
    DOOM::VERTEX h_f_tail = horiz_head;
    player->horizon.head = h_f_head;
    player->horizon.tail = h_f_tail;
    return player;
}

void PLAYER_rotate_camera(PLAYER* player, SDL_Event event) {
    const uint8_t* keystates = SDL_GetKeyboardState(NULL);
    int xrel, yrel;

    SDL_GetRelativeMouseState(&xrel, &yrel);

    if (xrel != 0) player->direction += (xrel / MOUSE_SENS);

    if (keystates[SDL_SCANCODE_LEFT]) player->direction -= (M_PI / KEY_SENS);

    if (keystates[SDL_SCANCODE_RIGHT]) player->direction += (M_PI / KEY_SENS);

    if (player->direction > 2.0 * M_PI) {
        player->direction -= (2.0 * M_PI);
    } else if (player->direction < 0) {
        player->direction += (2.0 * M_PI);
    }
    DOOM::VERTEX dir_head = {player->position.head.x + cos(player->direction),
                             0,
                             player->position.head.z - sin(player->direction)};
    player->dir_vector.head = dir_head;

    DOOM::VERTEX horiz_tail = player->dir_vector.head;
    horiz_tail.x += (cos(player->direction) * HORIZON_DIST);
    horiz_tail.z -= (sin(player->direction) * HORIZON_DIST);
    double hor_dir = player->direction + (M_PI / 2.0);
    DOOM::VERTEX horiz_head = {horiz_tail.x + (cos(hor_dir) * HORIZ_LEN), 0,
                               horiz_tail.z - (sin(hor_dir) * HORIZ_LEN)};
    DOOM::VERTEX h_f_head = horiz_head;

    horiz_tail = player->dir_vector.head;
    horiz_tail.x += (cos(player->direction) * HORIZON_DIST);
    horiz_tail.z -= (sin(player->direction) * HORIZON_DIST);
    hor_dir = player->direction - (M_PI / 2.0);
    horiz_head.x = horiz_tail.x + (cos(hor_dir) * HORIZ_LEN);
    horiz_head.z = horiz_tail.z - (sin(hor_dir) * HORIZ_LEN);
    DOOM::VERTEX h_f_tail = horiz_head;
    player->horizon.head = h_f_head;
    player->horizon.tail = h_f_tail;

    //   RVECTOR_print(player->dir_vector);
    //   printf("%.2lf %.2lf\n", player->direction / M_PI,
    //   RVECTOR_length(player->dir_vector));
}
