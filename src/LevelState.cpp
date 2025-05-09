#include "LevelState.h"



namespace NGIN {
    LevelState::LevelState(WALL* w, Sprite** s, size_t n) : walls(w), sprites(s),
    wallCount(n) {
        this->wallColors = new uint32_t[n];
        for (size_t i = 0; i < n; ++i) {
            this->wallColors[i] = this->walls[i].color;
        }
    };


}


