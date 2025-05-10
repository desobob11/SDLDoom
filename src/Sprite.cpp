#include "Sprite.h"
#include "Const.h"



namespace NGIN {
    Sprite::Sprite(std::string n, DOOM::VERTEX p) : 
    name(n), dist(0), columnStart(SCREEN_WIDTH + 1), scale(NGIN::SPRITE_SCALE_BASE) {
        this->pos = DOOM::Vector {p, DOOM::VERTEX {0, 0, 0}};
    };

    DOOM::VERTEX* Sprite::getHitBox() {
        DOOM::VERTEX* hitBox = new DOOM::VERTEX[4];
        DOOM::VERTEX pos = this->pos.head;
        hitBox[0] = DOOM::VERTEX {pos.x - (SPRITE_HBOX_DIM / 2), 0, pos.z - (SPRITE_HBOX_DIM / 2)};
        hitBox[1] = DOOM::VERTEX {pos.x + (SPRITE_HBOX_DIM / 2), 0, pos.z - (SPRITE_HBOX_DIM / 2)};
        hitBox[2] = DOOM::VERTEX {pos.x - (SPRITE_HBOX_DIM / 2), 0, pos.z + (SPRITE_HBOX_DIM / 2)};
        hitBox[3] = DOOM::VERTEX {pos.x + (SPRITE_HBOX_DIM / 2), 0, pos.z + (SPRITE_HBOX_DIM / 2)};
        return hitBox;
    }
}