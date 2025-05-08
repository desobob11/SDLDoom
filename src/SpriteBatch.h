#ifndef SPRITEBATCH_H_
#define SPRITEBATCH_H_

#include "Sprite.h"
#include <vector>
#include <array>
#include <map>
#include "../SDL2/include/SDL2/SDL.h"
#include <sstream>
#include <fstream>
#include "Const.h"

#define PARSE_SIZE 4096
#define LOOKUP_TABLE "./assets/lookup.txt"
#define SCALE_UP_F 4

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
            uint32_t q_interp(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
        public:
            void loadImages();
            void addSprite(Sprite* s);
            void renderSprites(SDL_Surface* surf);
            SCALED_SPRITE scaleDown(double factor, uint32_t* img, uint32_t h, uint32_t w);
            SCALED_SPRITE scaleUp(float factor, uint32_t* img, uint32_t h, uint32_t w);
            static std::map<std::string, std::pair<uint32_t, uint32_t>> lookupTable; 
            SpriteBatch();
            ~SpriteBatch();
            void updateSpriteDistances(DOOM::Vector playerPos);
        
    };


}


#endif