#ifndef SPRITEBATCH_H_
#define SPRITEBATCH_H_

#include "Sprite.h"
#include <vector>
#include <array>
#include <map>
#include "../SDL2/include/SDL2/SDL.h"

namespace NGIN {
    class SpriteBatch {
        private:
            std::vector<Sprite&> sprites;
            std::map<std::string, uint32_t*> imgs;

        public:
            void addSprite(Sprite& s);
            void renderSprites(SDL_Surface* surf);
    };


}


#endif