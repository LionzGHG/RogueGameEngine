
#include "math.h"

Vec Vec2(float x, float y) {
    return (Vec){x, y, 0.0f};
}

Vec Vec3(float x, float y, float z) {
    return (Vec){x, y, z};
}