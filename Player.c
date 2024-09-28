#include "Player.h"

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