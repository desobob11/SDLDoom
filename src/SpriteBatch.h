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

    typedef struct SCALED_SPRITE {
        double factor;
        uint32_t* img;
        uint32_t h;
        uint32_t w;
    } SCALED_SPRITE;


    class SpriteBatch {
        private:
            std::vector<Sprite*> sprites;
            std::map<std::string, uint32_t*> imgs;
            void loadImage(Sprite sp);
            static void loadLookup();
        public:
            void loadImages();
            void addSprite(Sprite* s);
            void renderSprites(SDL_Surface* surf);
            SCALED_SPRITE scaleDown(double factor, uint32_t* img, uint32_t h, uint32_t w);
            static std::map<std::string, std::pair<uint32_t, uint32_t>> lookupTable; 
            SpriteBatch();
        
    };


}


#endif