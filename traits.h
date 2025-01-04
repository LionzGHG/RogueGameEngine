
#ifndef ROGUE_TRAITS_H
#define ROGUE_TRAITS_H

#include "core.h"
#include "math.h"

typedef struct Trait Trait;
typedef struct Actor Actor;

#define TR_TRANSFORM "Transform"

typedef struct Transform {
    Trait* trait;
    Vec position;
    Vec scale;
} Transform;

Trait* InitTransform();

#endif