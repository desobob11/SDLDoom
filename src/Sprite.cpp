#include "Sprite.h"




namespace NGIN {
    Sprite::Sprite(std::string n, DOOM::VERTEX p) : 
    name(n), dist(0), scale(NGIN::SPRITE_SCALE_BASE) {
        this->pos = DOOM::Vector {p, DOOM::VERTEX {0, 0, 0}};
    };
}