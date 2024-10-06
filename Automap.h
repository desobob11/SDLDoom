#ifndef AUTOMAP_H_
#define AUTOMAP_H_

#include <stdio.h>
#include <stdlib.h>




typedef struct MAP {
    int h;
    int w;
    uint32_t * map;
} MAP;




uint32_t* AUTOMAP_create_map(MAP amap, uint32_t* arr);















#endif