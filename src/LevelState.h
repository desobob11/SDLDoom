#ifndef LEVELSTATE_H_
#define LEVELSTATE_H_
#include "../SDL2/include/SDL2/SDL.h"

typedef struct WALL {
    uint32_t color;
    uint32_t x_pos;
    uint32_t z_pos;
} WALL;


class LevelState {
    public:
        WALL* walls;
        
};
#endif
