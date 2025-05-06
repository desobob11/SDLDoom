#ifndef SPRITE_H_
#define SPRITE_H_
#include <stdint.h>

namespace DOOM {
    class Sprite {
        public:
            uint32_t img[128][128];



            void render();
    };
}







#endif