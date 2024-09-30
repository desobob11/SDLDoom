#include "RVector.h"
#define WALL_SIZE 50




uint32_t GAME_max(uint32_t x, uint32_t y) {
    if (x > y) {
        return x;
    }
    return y;
}


RVECTOR RVECTOR_diff(RVECTOR v1, RVECTOR v2) {
   // RVECTOR v3 = {v2.x - v1.x, v2.y - v1.y, v2.z - v1.z};
   // RVECTOR v = {v1.x + v3.x, v1.y + v3.y, v1.z + v3.z};
    return v1;
}

RVECTOR RVECTOR_cast(RVECTOR v1, RVECTOR v2) {
    RVECTOR v = {v2.head, v1.head};
    return v;
}

uint32_t RVECTOR_darken_color(uint32_t color, uint32_t distance) {
    uint32_t r, g, b;

    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = (color) & 0xFF;

    r = GAME_max(r - (3 * distance), 0x00);
    g = GAME_max(g - (3 * distance), 0x00);
    b = GAME_max(b - (3 * distance), 0x00);

    uint32_t darkened = 0x00000000;

    darkened |= (r << 16);
    darkened |= (g << 8);
    darkened |= b;

    return darkened;

}

////   RVERTEX start_pos = {75, 0, 0};
DRAW_COL RVECTOR_cast_seek_length(RVECTOR v, int* map, int map_width) {
    int hit = 0;
    RVECTOR copy = v;
    DRAW_COL col;
    // assuming this function is only cast using normalized direction vector
     // fro player's position
     double x_incr = fabs(v.head.x - v.tail.x);
     double z_incr = fabs(v.head.z - v.tail.z);

    
    while (!hit) {
  
        int i = (int) copy.head.z / WALL_SIZE;
        int j = (int) copy.head.x / WALL_SIZE;
       // printf("Head at (%d, %d)\n", i, j);
        if (*(map + ((i * map_width) + j))) {
           // printf("Wall Found at (%.2lf, %.2lf)\n", copy.head.x, copy.head.z);
            int x_mod = (int) copy.head.x % WALL_SIZE;
            int z_mod = (int) copy.head.z % WALL_SIZE;

            int corner_a = x_mod % WALL_SIZE == 0 && z_mod % WALL_SIZE  == 0;
            int corner_b = x_mod % WALL_SIZE == WALL_SIZE - 1 && z_mod % WALL_SIZE  == WALL_SIZE - 1;

            col.distance = RVECTOR_length(copy);

            if (corner_a || corner_b) {
                col.color = 0x00000000;
            }
            else {
                //printf("here\n");
                col.color = RVECTOR_darken_color(*(map + ((i * map_width) + j)), (uint32_t) col.distance) ;
            }

            //col.color = *(map + ((i * map_width) + j));
            hit = 1;
        }
        else {
            RVERTEX new_head = {copy.head.x + x_incr, 0, copy.head.z + z_incr};
            copy.head = new_head;
        }
    }
    return col;
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

