#ifndef Vector_H_
#define Vector_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../SDL2/include/SDL2/SDL.h"
#include "Wall.h"

namespace DOOM {

typedef struct DRAW_COL {
    uint32_t color;
    double distance;
} DRAW_COL;

typedef struct VERTEX {
    double x;
    double y;
    double z;
} VERTEX;

typedef struct Vector {
    VERTEX head;
    VERTEX tail;
} Vector;

class Vector {
   public:
    VERTEX head;
    VERTEX tail;

    Vector(const Vector& other) : head(other.head), tail(other.tail) {};

    uint32_t GAME_max(uint32_t x, uint32_t y);
    Vector Vector_normalize() const;
    static Vector Vector_diff(Vector v1, Vector v2);
    void Vector_print() const;
    static Vector Vector_cast(Vector v1, Vector v2);
    double Vector_length() const;
    int Vector_draw_height(double length);
    DRAW_COL Vector_cast_seek_length(SDL_Renderer* rend,
                                      Vector h_point, uint32_t* walls,
                                      int map_w, int map_h) const;
    uint32_t static Vector_darken_color(uint32_t color, uint32_t distance);
    static VERTEX Vector_closest_point(VERTEX ray_head, Vector horizon);
    Vector Vector_rotate_vector(double theta, Vector vector);
};
}  // namespace DOOM

#endif
