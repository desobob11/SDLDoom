#include "RVector.h"


#define SIZE 50
#define WIDTH 800

#define MAP_HEIGHT SIZE * 3;
#define MAP_WIDTH SIZE * 3;

RVECTOR RVECTOR_diff(RVECTOR v1, RVECTOR v2) {
   // RVECTOR v3 = {v2.x - v1.x, v2.y - v1.y, v2.z - v1.z};
   // RVECTOR v = {v1.x + v3.x, v1.y + v3.y, v1.z + v3.z};
    return v1;
}

RVECTOR RVECTOR_cast(RVECTOR v1, RVECTOR v2) {
    RVECTOR v = {v2.head, v1.head};
    return v;
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

void RVECTOR_print(RVECTOR v) {

    printf("Tail: (%.2lf, %.2lf, %.2lf) Head: (%.2lf, %.2lf, %.2lf)\n", v.tail.x, v.tail.y, v.tail.z,
    v.head.x, v.head.y, v.head.z);
}

int main() {



    
   // int map[3][3] = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
    //                    {0, 0, 0,},
     //                   {0,0,0}};

    //int p_x = 75, p_y = 75;
    //int wall_x = 75, wall_y = 150;


    RVECTOR p_pos;
    RVERTEX v = {0, 0, 0};
    p_pos.tail = v;
    v.x = 75; v.z = 75;
    p_pos.head = v;



    RVECTOR w_pos;
    v.x = 0; v.z = 0;
    w_pos.tail = v;
    v.x = 40; v.z = 150;
    w_pos.head = v;


    RVECTOR diff = RVECTOR_cast(p_pos, w_pos);
    RVECTOR_print(diff);
    printf("%.2lf\n", RVECTOR_length(diff));


    return 0;
}