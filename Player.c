#include "Player.h"
#include <math.h>

#define MOUSE_SENS 50.0

void move_player(PLAYER *player, SDL_Event event, int l_width, int l_height)
{
    if (event.type == SDL_KEYDOWN)
    {
        RVERTEX newPos = player->position.head;
        SDL_Scancode code = event.key.keysym.scancode;
        if (code == SDL_SCANCODE_W)
        {
            if (newPos.z + 1 < l_height)
                newPos.z += 1;
        }
        if (code == SDL_SCANCODE_S)
        {
            if (newPos.z - 1 >= 0)
                newPos.z -= 1;
        }
        if (code == SDL_SCANCODE_A)
        {
            if (newPos.x - 1 >= 0)
                newPos.x -= 1;
        }
        if (code == SDL_SCANCODE_D)
        {
            if (newPos.x + 1 < l_width)
                newPos.x += 1;
        }
        player->position.head = newPos;
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
    return player;
}

void *PLAYER_rotate_camera(PLAYER *player, SDL_Event event)
{   
    if (event.type == SDL_KEYDOWN)
    {
        SDL_Scancode code = event.key.keysym.scancode;
        if (code == SDL_SCANCODE_LEFT)
            player->direction += (M_PI / MOUSE_SENS);
        if (code == SDL_SCANCODE_RIGHT)
            player->direction -= (M_PI / MOUSE_SENS);
        if (player->direction > 2.0 * M_PI) {
            player->direction -= (2.0 * M_PI);
        }
        else if (player->direction < 0)
        {
            player->direction += (2.0 * M_PI);
        }
        RVERTEX dir_head = {player->position.head.x + cos(player->direction), 0, player->position.head.z + sin(player->direction)};
        player->dir_vector.head = dir_head;
        RVECTOR_print(player->dir_vector);
        printf("%.2lf %.2lf\n", player->direction / M_PI, RVECTOR_length(player->dir_vector));
    }
}

