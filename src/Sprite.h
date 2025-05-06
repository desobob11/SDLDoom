#ifndef SPRITE_H_
#define SPRITE_H_
#include <stdint.h>

#include <iostream>
#include <string>

namespace NGIN {
typedef struct Sprite {
    // private:
    std::string name;
    uint32_t x;
    uint32_t z;

    // public:

    //  Sprite(std::string name, uint32_t w, uint32_t h, uint32_t x, uint32_t z)
    //     : name(name), w(w), h(h), x(x), z(z) {};
} Sprite;
}  // namespace NGIN

#endif