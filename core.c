
#include "core.h"
#include <stdlib.h>
#include <stdio.h>
#include "assets.h"


Scene* InitScene(const char* name, void (*update)(Scene* this, float dt)) {
    Scene* scene = (Scene*)malloc(sizeof(Scene));

    if (!scene) {
        fprintf(stderr, "ERROR: Memory allocation for new Scene failed!\n");
        exit(EXIT_FAILURE);
    }

    //scene->asset.name = name;   
    scene->update = update;

    scene->actors = NULL;
    scene->numActors = 0;

    //LoadAsset((Asset*)scene);
    return scene;
}

void DestroyScene(Scene* scene) {
    for (size_t i = 0; i < scene->numActors; ++i) {
        DestroyActor(&scene->actors[i]);
    }
    free(scene);
}

void SetScene(Window* window, Scene* scene) {
    window->activeScene = scene;
}

Scene* GetScene(Window* window) {
    return window->activeScene;
}

Actor* GetActor(Scene* scene, const char* id) {
    for (size_t i = 0; i < scene->numActors; ++i) {
        Actor* actor = &scene->actors[i];
        if (strcmp(actor->id, id) == 0) {
            return actor;
        }
    }

    fprintf(stderr, "ERROR: Actor '%s' does not exist in this Scene!\n", id);
    exit(EXIT_FAILURE);
}

void AddActor(Scene* scene, Actor* actor) {
    Actor** newActors = (Actor**)realloc(scene->actors, sizeof(Actor*) * (scene->numActors + 1));

    if (!newActors) {
        fprintf(stderr, "ERROR: Memory allocation for new actor failed.\n");
        return;
    }

    newActors[scene->numActors] = actor;
    scene->actors = *newActors;
    scene->numActors++;
}

Actor* InitActor(const char* id) {
    Actor* actor = (Actor*)malloc(sizeof(Actor));

    if (!actor) {
        fprintf(stderr, "ERROR: Memory allocation for new actor failed!\n");
        exit(EXIT_FAILURE);
    }

    actor->id = strdup(id);
    actor->numTraits = 0;
    actor->traits = NULL;

    actor->transform = (Transform*)InitTransform();

    return actor;
}

void DestroyActor(Actor* actor) {
    free(actor->id);
    free(actor->traits);
    free(actor);
}

void AddTrait(Actor* actor, Trait* trait) {
    Trait** newTraits = (Trait**)realloc(actor->traits, sizeof(Trait*) * (actor->numTraits + 1));

    if (!newTraits) {
        fprintf(stderr, "ERROR: Failed to allocate memory for traits!\n");
        return;
    }

    newTraits[actor->numTraits] = trait;
    actor->traits = *newTraits;
    actor->numTraits++;
}

Trait* GetTrait(Actor* actor, const char* id) {
    for (int i = 0; i < actor->numTraits; i++) {
        Trait* trait = &actor->traits[i];
        if (trait && trait->id && strcmp(trait->id, id) == 0) {
            return trait;
        }
    }
    printf("WARNING: Actor %s has no Trait %s!\n", actor->id, id);
    return NULL;
}