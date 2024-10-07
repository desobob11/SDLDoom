#include "Automap.h"


MAP current_map;


uint32_t* AUTOMAP_create_map(MAP amap, uint32_t* arr) {
    uint32_t* map = (uint32_t*) calloc(amap.h * amap.w, sizeof(uint32_t));

    for (int i = 0; i < amap.h; ++i) {
        for (int j = 0; j < amap.w; ++j) {
            map[(j * i) + j] = arr[(j * i) + j];
        }
    }    
    return map;
}

void AUTOMAP_render_map(uint32_t map, PLAYER *player) {



    
}
