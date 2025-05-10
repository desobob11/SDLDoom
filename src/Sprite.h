#ifndef SPRITE_H_
#define SPRITE_H_
#include <stdint.h>
#include "Vector.h"
#include <iostream>
#include <string>



namespace NGIN {

class Sprite {
    // private:
    public:
        std::string name;
        DOOM::Vector pos;
        float dist;
        uint32_t columnStart;
        int32_t scale;
        Sprite(std::string n, DOOM::VERTEX p);
        DOOM::VERTEX* getHitBox();
    // public:

    //  Sprite(std::string name, uint32_t w, uint32_t h, uint32_t x, uint32_t z)
    //     : name(name), w(w), h(h), x(x), z(z) {};
};

const uint32_t SPRITE_HBOX_DIM = 2;
inline const int32_t SPRITE_SCALE_BASE = 2, SPRITE_SCALE_MAX = 5, SPRITE_SCALE_MIN = 0;
inline float SPRITE_SCALES[] {0.25, 0.50, 1.0, 2.0, 3.0, 4.0};
}  // namespace NGIN

#endif