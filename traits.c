
#include <stdio.h>
#include "traits.h"

Trait* InitTransform() {
    Transform* transform = (Transform*)malloc(sizeof(Transform));

    if (!transform) {
        fprintf(stderr, "ERROR: Memory allocation for Transform failed!\n");
        exit(EXIT_FAILURE);
    } 

    transform->trait = (Trait*)malloc(sizeof(Trait));
    if (!transform->trait) {
        fprintf(stderr, "ERROR: Memory allocation for Transform trait failed!\n");
        exit(EXIT_FAILURE);
    }
    transform->trait->id = TR_TRANSFORM;
    
    transform->position = Vec2(100.0f, 100.0f);
    transform->scale = Vec2(100.0f, 100.0f);

    return (Trait*)transform;
}
