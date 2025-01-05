
#ifndef ROGUE_CORE_H
#define ROGUE_CORE_H

#include "window.h"
#include "assets.h"
#include "traits.h"

typedef struct Asset Asset;
typedef struct Window Window;
typedef struct Actor Actor;
typedef struct Trait Trait;
typedef struct Transform Transform;

typedef struct Scene {
    //Asset asset;
    Actor* actors;
    int numActors;
    void (*update)(struct Scene* this, float dt);
} Scene;

typedef struct Actor {
    const char* id;
    Trait* traits;
    int numTraits;
    Transform* transform;
} Actor;

typedef struct Trait {
    const char* id;
} Trait;

Scene* InitScene(const char* name, void (*update)(Scene* this, float dt));
void DestroyScene(Scene* scene);
void SetScene(Window* window, Scene* scene);
Scene* GetScene(Window* window);
void AddActor(Scene* scene, Actor* actor);
Actor* GetActor(Scene* scene, const char* id);

Actor* InitActor(const char* id);
void DestroyActor(Actor* actor);
void AddTrait(Actor* actor, Trait* trait);
Trait* GetTrait(Actor* actor, const char* id);

#endif