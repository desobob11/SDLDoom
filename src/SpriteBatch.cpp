#include "SpriteBatch.h"


namespace NGIN {
    void SpriteBatch::addSprite(Sprite& s) {
        this->sprites.push_back(s);
    }

    void SpriteBatch::renderSprites(SDL_Surface* surface) {
        uint32_t *pixels = (uint32_t *) surface->pixels;

        for (Sprite sp : this->sprites) {
            uint32_t* img = this->imgs[sp.name];
            for (uint32_t i = 0; i < sp.h; ++i) {
                for (uint32_t j = 0; j < sp.w; ++j) {
                    pixels[((i * sp.w)) + j] = img[((i * sp.w)) + j];
                }
            }
        }
    }


   // uint32_t *pixels = (uint32_t *)surface->pixels;







}