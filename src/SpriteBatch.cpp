#include "SpriteBatch.h"

using namespace std;

namespace NGIN {

    std::map<std::string, std::pair<uint32_t, uint32_t>> SpriteBatch::lookupTable {};

    void SpriteBatch::addSprite(Sprite* s) {
        this->sprites.push_back(s);
    }

    void SpriteBatch::renderSprites(SDL_Surface* surface) {
        uint32_t *pixels = (uint32_t *) surface->pixels;

        for (Sprite* sp : this->sprites) {
            uint32_t* img = this->imgs[(*sp).name];
            
            uint32_t h = this->lookupTable[(*sp).name].first;
            uint32_t w = this->lookupTable[(*sp).name].second;

            SCALED_SPRITE ss = scaleDown(sp->scale, img, h, w);

            for (uint32_t i = 0; i < ss.h; ++i) {
                for (uint32_t j = 0; j < ss.w; ++j) {
                    pixels[(i * surface->w) + j] = ss.img[(i * ss.w) + j];
                }
            }
        }
    }

    void SpriteBatch::loadImage(Sprite sp) {
        std::stringstream sb {};
        sb << "./assets/" << sp.name << ".dat";
        std::string fname = sb.str();

        std::ifstream file {fname, std::ios::binary};
        if (file.is_open()) {
            uint32_t h = this->lookupTable[sp.name].first;
            uint32_t w = this->lookupTable[sp.name].second;
            cout << h << " " << w << endl;

            size_t offset = 0;
            uint32_t* imgArr = new uint32_t[h*w];
            while (file.read(reinterpret_cast<char*>(imgArr + offset), sizeof(uint32_t))) {
                ++offset;
            }
            this->imgs[sp.name] = imgArr;
        }


    }

    void SpriteBatch::loadImages() {
        for (Sprite* sp : this->sprites) {
            if (this->imgs.find((*sp).name) == this->imgs.end()) {
                this->loadImage(*sp);
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

                uint32_t height = static_cast<uint32_t>(std::stoi(line.substr(0, line.find(","))));
                line.erase(0, line.find(",") + 1);  // "length" = 1

                uint32_t width = static_cast<uint32_t>(std::stoi(line.substr(0, line.find(","))));
                line.erase(0, line.find(",") + 1);  // "length" = 1
                
                std::pair<uint32_t, uint32_t> hw {height, width};

                SpriteBatch::lookupTable[name] = hw;
            }
        }
    }

    SpriteBatch::SpriteBatch() {
        if (SpriteBatch::lookupTable.size() == 0) {
            SpriteBatch::loadLookup();
        }
    }



    SCALED_SPRITE SpriteBatch::scaleDown(double factor, uint32_t* img, uint32_t height, uint32_t width) {
        uint32_t h = static_cast<uint32_t>(height * factor);
        uint32_t w = static_cast<uint32_t>(width * factor);

        size_t w_iter = static_cast<size_t>(width / w);
        size_t h_iter = static_cast<size_t>(height / h);

        size_t img_i = 0;
        uint32_t* scaledImg = new uint32_t[h*w];
        for (size_t i = 0; i < h; ++i) {
            size_t img_j = 0;
            for (size_t j = 0; j < w; ++j) {
                scaledImg[(i*w) + j] = img[(img_i*width) + img_j];
                img_j += w_iter;
            }
            img_i += h_iter;
        }
        return SCALED_SPRITE {factor, scaledImg, h, w};
    }


    
    SCALED_SPRITE SpriteBatch::scaleUp(double factor, uint32_t* img, uint32_t height, uint32_t width) {


        uint32_t h = static_cast<uint32_t>(height * factor);
        uint32_t w = static_cast<uint32_t>(width * factor);

        size_t w_iter = static_cast<size_t>(width / w);
        size_t h_iter = static_cast<size_t>(height / h);

        size_t img_i = 0;
        uint32_t* scaledImg = new uint32_t[h*w];
        for (size_t i = 0; i < h; ++i) {
            size_t img_j = 0;
            for (size_t j = 0; j < w; ++j) {
                scaledImg[(i*w) + j] = img[(img_i*width) + img_j];
                img_j += w_iter;
            }
            img_i += h_iter;
        }
        return SCALED_SPRITE {factor, scaledImg, h, w};
    }

    /*
        Interoplates 4 
    */
    uint32_t SpriteBatch::q_interp(uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
        uint8_t abc = !((a ^ b) | (a ^ c));
        uint8_t abd = !((a ^ b) | (a ^ d));
        uint8_t bcd = !((b ^ c) | (b ^ d));
        uint8_t acd = !((a ^ c) | (a ^ d));

        // three pixels equal, return them
        if (abc | abd | bcd | acd) {
            return a;
        }

        uint32_t r, g, b;
        uint32_t arr[] {a, b, c, d};

        // sum r g and b channels
        for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
            r += (arr[i] >> 16) & 0xFF;
            g += (arr[i] >> 8) & 0xFF;
            b += (arr[i]) & 0xFF;
        }

        // average each channel
        r /= sizeof(arr);
        g /= sizeof(arr);
        b /= sizeof(arr);
        
        // merge channels and return
        uint32_t result = 0x00000000;
        result |= (r << 16);
        result |= (g << 8);
        result |= b;
        return result;
    }



   // uint32_t *pixels = (uint32_t *)surface->pixels;







}