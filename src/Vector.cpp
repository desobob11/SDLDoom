#include "Vector.h"

#include <algorithm>

#include "Automap.h"
#include "Const.h"


namespace DOOM {

Vector Vector::Vector_cast(Vector v1, Vector v2) {
    Vector v = Vector{v2.head, v1.head};
    return v;
}

uint32_t Vector::Vector_darken_color(uint32_t color, uint32_t distance) {
    if (distance >= 4 * BLOCK_SIZE) return 0x00;
    uint32_t r, g, b;

    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = (color) & 0xFF;

    r = std::max(r * (1 - (distance / 800.0)), (double)0x00);
    g = std::max(g * (1 - (distance / 800.0)), (double)0x00);
    b = std::max(b * (1 - (distance / 800.0)), (double)0x00);

    uint32_t darkened = 0x00000000;

    darkened |= (r << 16);
    darkened |= (g << 8);
    darkened |= b;

    return darkened;
}



Vector Vector::Vector_normalize() const {
    Vector norm = {this->head, this->tail};
    double inverse_length = 1 / norm.Vector_length();
    norm.head.x *= inverse_length;
    norm.head.y *= inverse_length;
    norm.head.z *= inverse_length;
    return norm;
}

double Vector::Vector_length() const {
    double x = (this->head.x - this->tail.x);
    x *= x;

    double y = (this->head.y - this->tail.y);
    y *= y;

    double z = (this->head.z - this->tail.z);
    z *= z;

    return sqrt(x + y + z);
}

int Vector_draw_height(double length) { return 1; }

void Vector::Vector_print() const {
    printf("Tail: (%.2lf, %.2lf, %.2lf) Head: (%.2lf, %.2lf, %.2lf)\n",
           this->tail.x, this->tail.y, this->tail.z, this->head.x, this->head.y,
           this->head.z);
}

VERTEX Vector::Vector_closest_point(VERTEX ray_head, Vector horizon) {
    if (horizon.head.x == horizon.tail.x) {
        VERTEX p = {horizon.tail.x, 0, ray_head.z};
        return p;
    }
    if (horizon.head.z == horizon.tail.z) {
        VERTEX p = {ray_head.x, 0, horizon.tail.z};
        return p;
    }
    double m1 =
        (horizon.head.z - horizon.tail.z) / (horizon.head.x - horizon.tail.x);
    double m2 = -(1.0 / m1);
    double point_x = ((m1 * horizon.tail.x) - (m2 * ray_head.x) -
                      horizon.tail.z + ray_head.z) /
                     (m1 - m2);
    double point_z = (m2 * (point_x - ray_head.x)) + ray_head.z;
    VERTEX point = {point_x, 0, point_z};
    return point;
}

Vector Vector::Vector_rotate_vector(double theta, Vector vector) {
    Vector to_return;
    VERTEX temp_head = {vector.head.x - vector.tail.x, 0,
                        vector.head.z - vector.tail.z};
    VERTEX origin = {0, 0, 0};
    Vector temp = {temp_head, origin};

    to_return.head.x = (temp.head.x * cos(theta)) - (temp.head.z * sin(theta));
    to_return.head.z = (temp.head.x * sin(theta)) + (temp.head.z * cos(theta));
    to_return.head.x += vector.tail.x;
    to_return.head.z += vector.tail.z;
    to_return.tail = vector.tail;
    return to_return;
}
}  // namespace DOOM