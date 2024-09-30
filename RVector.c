#include "RVector.h"
#define WALL_SIZE 50

RVECTOR RVECTOR_diff(RVECTOR v1, RVECTOR v2) {
   // RVECTOR v3 = {v2.x - v1.x, v2.y - v1.y, v2.z - v1.z};
   // RVECTOR v = {v1.x + v3.x, v1.y + v3.y, v1.z + v3.z};
    return v1;
}

RVECTOR RVECTOR_cast(RVECTOR v1, RVECTOR v2) {
    RVECTOR v = {v2.head, v1.head};
    return v;
}

////   RVERTEX start_pos = {75, 0, 0};
double RVECTOR_cast_seek_length(RVECTOR v, int* map, int map_width) {
    int hit = 0;
    double length = -1;
    RVECTOR copy = v;
    // assuming this function is only cast using normalized direction vector
     // fro player's position
     double x_incr = fabs(v.head.x - v.tail.x);
     double z_incr = fabs(v.head.z - v.tail.z);

    
    while (!hit) {
  
        int i = (int) copy.head.z / WALL_SIZE;
        int j = (int) copy.head.x / WALL_SIZE;
       // printf("Head at (%d, %d)\n", i, j);
        if (*(map + ((i * map_width) + j))) {
            printf("Wall Found at (%d, %d)\n", i, j);
            length = RVECTOR_length(copy);
            hit = 1;
        }
        else {
            RVERTEX new_head = {copy.head.x + x_incr, 0, copy.head.z + z_incr};
            copy.head = new_head;
        }
    }

    return length;
}

RVECTOR RVECTOR_normalize(RVECTOR v) {
    RVECTOR norm = {v.head, v.tail};
    double inverse_length = 1 / RVECTOR_length(norm);
    norm.head.x *= inverse_length;
    norm.head.y *= inverse_length;
    norm.head.z *= inverse_length;
    return norm;
}

double RVECTOR_length(RVECTOR v) {
    double x = (v.head.x - v.tail.x);
    x *= x;

    double y = (v.head.y - v.tail.y);
    y *= y;

    double z = (v.head.z - v.tail.z);
    z *= z;

    return sqrt(x + y + z);

}

int RVECTOR_draw_height(double length) {
    return 1;
}

void RVECTOR_print(RVECTOR v) {

    printf("Tail: (%.2lf, %.2lf, %.2lf) Head: (%.2lf, %.2lf, %.2lf)\n", v.tail.x, v.tail.y, v.tail.z,
    v.head.x, v.head.y, v.head.z);
}

