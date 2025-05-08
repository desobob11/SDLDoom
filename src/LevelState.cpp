#include "LevelState.h"

#include <stdio.h>


namespace NGIN {
    LevelState::LevelState(WALL* w, Sprite** s) : walls(w), sprites(s) {};

    void LevelState::updateSpriteDistances(DOOM::Vector playerPos) {
        this->batch.updateSpriteDistances(playerPos);
    }

}


