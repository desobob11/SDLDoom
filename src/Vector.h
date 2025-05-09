#ifndef Vector_H_
#define Vector_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../SDL2/include/SDL2/SDL.h"


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

class Vector {
   public:
    VERTEX head;
    VERTEX tail;

    Vector(VERTEX head, VERTEX tail) : head(head), tail(tail) {};
    Vector(const Vector& other) : head(other.head), tail(other.tail) {};
    Vector() {};

    uint32_t GAME_max(uint32_t x, uint32_t y);
    Vector Vector_normalize() const;
    void Vector_print() const;
    static Vector Vector_cast(Vector v1, Vector v2);
    double Vector_length() const;
    int Vector_draw_height(double length);
    DRAW_COL Vector_cast_seek_length(SDL_Renderer* rend, Vector h_point, NGIN::LevelState ls, int map_w,
                                     int map_h, uint32_t pixelCol) const;
    static uint32_t Vector_darken_color(uint32_t color, uint32_t distance);
    static VERTEX Vector_closest_point(VERTEX ray_head, Vector horizon);
    static Vector Vector_rotate_vector(double theta, Vector vector);
    /*
    inline friend Vector operator-(const Vector& a,const Vector& b) {

        return Vector {a.tail, b.tail};
    }

    inline friend Vector operator+(const Vector& a,const Vector& b) {
        return Vector {a.tail, b.head};
    }
        */
};
}  // namespace DOOM

#endif
