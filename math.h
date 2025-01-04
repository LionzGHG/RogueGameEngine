
#ifndef ROGUE_MATH_H
#define ROGUE_MATH_H

typedef struct Vec {
    float x, y, z;
} Vec;

#define VEC2_ZERO   vec2(0.0f, 0.0f)
#define VEC2_UP     vec2(0.0f, 1.0f)
#define VEC2_DOWN   vec2(0.0f, -1.0f)
#define VEC2_LEFT   vec2(-1.0f, 0.0f)
#define VEC2_RIGHT  vec2(1.0f, 0.0f)

#define VEC3_ZERO   vec3(0.0f, 0.0f, 0.0f)
#define VEC3_UP     vec3(0.0f, 1.0f, 0.0f)
#define VEC3_DOWN   vec3(0.0f, -1.0f, 0.0f)
#define VEC3_LEFT   vec3(-1.0f, 0.0f, 0.0f)
#define VEC3_RIGHT  vec3(1.0f, 0.0f, 0.0f)

Vec Vec2(float x, float y);
Vec Vec3(float x, float y, float z);

#endif