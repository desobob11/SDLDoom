#ifndef LEVELSTATE_H_
#define LEVELSTATE_H_
#include "../SDL2/include/SDL2/SDL.h"
#include "Sprite.h"
#include "SpriteBatch.h"
#include "Vector.h"

namespace NGIN {
typedef struct WALL {
    uint32_t color;
    uint32_t x_pos;
    uint32_t z_pos;
} WALL;


class LevelState {
    public:
        WALL* walls;
        Sprite** sprites;
        LevelState(WALL* w, Sprite** s);
        void updateSpriteDistances(DOOM::Vector playerPos);
        SpriteBatch batch;
    private:

};
}
#endif
