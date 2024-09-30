#ifndef RVECTOR_H_
#define RVECTOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


typedef struct DRAW_COL {
    uint32_t color;
    double distance;
} DRAW_COL;

typedef struct RVERTEX {
    double x;
    double y;
    double z;
} RVERTEX;

typedef struct RVECTOR
{
    RVERTEX head;
    RVERTEX tail;
} RVECTOR;

RVECTOR RVECTOR_normalize(RVECTOR v);
RVECTOR RVECTOR_diff(RVECTOR v1, RVECTOR v2);
void RVECTOR_print(RVECTOR v);
RVECTOR RVECTOR_cast(RVECTOR v1, RVECTOR v2);
double RVECTOR_length(RVECTOR v);
int RVECTOR_draw_height(double length);
DRAW_COL RVECTOR_cast_seek_length(RVECTOR v1, int* map, int map_width);

#endif
