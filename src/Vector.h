#ifndef Vector_H_
#define Vector_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// THIS IS BAD


#include "../SDL2/include/SDL2/SDL.h"


namespace DOOM {

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
    Vector(VERTEX head) : head(head) {};
    Vector(const Vector& other) : head(other.head), tail(other.tail) {};
    Vector() {};

    uint32_t GAME_max(uint32_t x, uint32_t y);
    Vector Vector_normalize() const;
    void Vector_print() const;
    static Vector Vector_cast(Vector v1, Vector v2);
    double Vector_length() const;
    int Vector_draw_height(double length);
    static uint32_t Vector_darken_color(uint32_t color, uint32_t distance);
    static VERTEX Vector_closest_point(VERTEX ray_head, Vector horizon);
    static Vector Vector_rotate_vector(double theta, Vector vector);
    bool overlapsBox(VERTEX topl, VERTEX topr, VERTEX botl, VERTEX botr);
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
