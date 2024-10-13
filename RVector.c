#include "RVector.h"
#include "Const.h"
#include "Automap.h"



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

    r = GAME_max(r * (1 - (distance /800.0)), 0x00);
    g = GAME_max(g * (1 - (distance /800.0)), 0x00);
    b = GAME_max(b * (1 - (distance /800.0)), 0x00);

    uint32_t darkened = 0x00000000;

    darkened |= (r << 16);
    darkened |= (g << 8);
    darkened |= b;



    return darkened;

}

////   RVERTEX start_pos = {75, 0, 0};
DRAW_COL RVECTOR_cast_seek_length(SDL_Renderer* rend, RVECTOR v, RVECTOR h_point, WALL* walls, int map_w, int map_h) {
  int hit = 0;
    RVECTOR copy = v;
    DRAW_COL col;

     double x_incr = v.head.x - v.tail.x;
     double z_incr = v.head.z - v.tail.z;

     int i = 0;
     int j = 0;
     while (!hit && (i >= 0 && i < map_h && j >= 0 && j < map_w))
     {
 
        i = (int)copy.head.z / BLOCK_SIZE;
        j = (int)copy.head.x / BLOCK_SIZE;
        if (walls[i*map_w + j].color)
        {
            int x_mod = (int)copy.head.x % BLOCK_SIZE;
            int z_mod = (int)copy.head.z % BLOCK_SIZE;

            int corner_a = x_mod % BLOCK_SIZE == 0 && z_mod % BLOCK_SIZE == 0;
            int corner_b = x_mod % BLOCK_SIZE == BLOCK_SIZE - 1 && z_mod % BLOCK_SIZE == BLOCK_SIZE - 1;

            copy.tail = RVECTOR_closest_point(copy.head, h_point);

            col.distance = RVECTOR_length(copy);
            col.color = RVECTOR_darken_color(walls[i*map_w + j].color, (uint32_t)col.distance);
            hit = 1;
            }
            else
            {
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



RVERTEX RVECTOR_closest_point(RVERTEX ray_head, RVECTOR horizon) {
    if (horizon.head.x == horizon.tail.x) {
        RVERTEX p = {horizon.tail.x, 0, ray_head.z};
        return p;
    }
    if (horizon.head.z == horizon.tail.z) {
        RVERTEX p = {ray_head.x, 0, horizon.tail.z};
        return p;
    }
    double m1 = (horizon.head.z - horizon.tail.z) / (horizon.head.x - horizon.tail.x);
    double m2 = -(1.0 / m1);
    double point_x = ((m1*horizon.tail.x) - (m2*ray_head.x) - horizon.tail.z + ray_head.z) / (m1 - m2);
    double point_z = (m2*(point_x - ray_head.x)) + ray_head.z;
    RVERTEX point = {point_x, 0, point_z};
    return point;
}