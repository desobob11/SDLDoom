#ifndef SPRITEBATCH_H_
#define SPRITEBATCH_H_

#include "Sprite.h"
#include <vector>
#include <array>
#include <map>
#include "../SDL2/include/SDL2/SDL.h"
#include <sstream>
#include <fstream>

#define PARSE_SIZE 4096
#define LOOKUP_TABLE "./assets/lookup.txt"

namespace NGIN {
    class SpriteBatch {
        private:
            std::vector<Sprite*> sprites;
            std::map<std::string, uint8_t*> imgs;
            void loadImages();
            void loadImage(Sprite sp);
            static void loadLookup();
        public:
            void addSprite(Sprite* s);
            void renderSprites(SDL_Surface* surf);
            static std::map<std::string, std::pair<uint32_t, uint32_t>> lookupTable; 
            SpriteBatch();
        
    };


}


#endif