#include "SpriteBatch.h"


namespace NGIN {

    std::map<std::string, std::pair<uint32_t, uint32_t>> SpriteBatch::lookupTable {};

    void SpriteBatch::addSprite(Sprite* s) {
        this->sprites.push_back(s);
    }

    void SpriteBatch::renderSprites(SDL_Surface* surface) {
        uint32_t *pixels = (uint32_t *) surface->pixels;

        for (Sprite* sp : this->sprites) {
            uint8_t* img = this->imgs[(*sp).name];
            for (uint32_t i = 0; i < (*sp).h; ++i) {
                for (uint32_t j = 0; j < (*sp).w; ++j) {
                    pixels[((i * (*sp).w)) + j] = img[((i * (*sp).w)) + j];
                }
            }
        }
    }

    void SpriteBatch::loadImage(Sprite sp) {
        std::stringstream sb {};
        sb << "../assets/" << sp.name << ".RAW";
        std::string fname = sb.str();

        std::ifstream file {fname, std::ios::binary};
        if (file.is_open()) {
            size_t offset = 0;
            uint8_t* imgArr = new uint8_t[sp.h * sp.w];
            while (!file.eof()) {
                file.read(reinterpret_cast<char*>(&imgArr + offset), PARSE_SIZE);
                offset += file.gcount();
            }
            this->imgs[sp.name] = imgArr;
        }


    }

    void SpriteBatch::loadImages() {
        for (Sprite* sp : this->sprites) {
            if (this->imgs.find((*sp).name) == this->imgs.end()) {
                this->loadImage((*sp));
            }
        }
    }


    void SpriteBatch::loadLookup() {
        std::ifstream file {LOOKUP_TABLE, std::ios::in};
        if (file.is_open()) {
            while (!file.eof()) {
                std::string line {};
                std::getline(file, line);

                std::string name = line.substr(0, line.find(","));
                line.erase(0, line.find(",") + 1);  // "length" = 1

                uint32_t width = static_cast<uint32_t>(std::stoi(line.substr(0, line.find(","))));
                line.erase(0, line.find(",") + 1);  // "length" = 1

                uint32_t height = static_cast<uint32_t>(std::stoi(line.substr(0, line.find(","))));
                line.erase(0, line.find(",") + 1);  // "length" = 1
                
                std::pair<uint32_t, uint32_t> hw {width, height};

                SpriteBatch::lookupTable[name] = hw;
            }
        }
    }

    SpriteBatch::SpriteBatch() {
        if (SpriteBatch::lookupTable.size() == 0) {
            SpriteBatch::loadLookup();
        }
    }


   // uint32_t *pixels = (uint32_t *)surface->pixels;







}