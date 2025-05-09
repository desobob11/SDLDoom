#include "LevelState.h"

#include <stdio.h>


namespace NGIN {
    LevelState::LevelState(WALL* w, Sprite** s) : walls(w), sprites(s) {
        this->wallColors = new uint32_t[sizeof(w) / sizeof(WALL)];
        for (size_t i = 0; i < sizeof(w) / sizeof(WALL); ++i) {
            this->wallColors[i] = this->walls[i].color;
        }
    };

    void LevelState::updateSpriteDistances(DOOM::Vector playerPos) {
        this->batch.updateSpriteDistances(playerPos);
    }

}


