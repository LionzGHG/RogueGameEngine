
#include <stdio.h>
#include "window.h"
#include "core.h"
#include "render.h"

int main() {
    Scene* myScene = InitScene();

    Actor* myActor = InitActor("My Actor");

    myActor->transform->scale = Vec2(400.0f, 250.0f);

    Trait* renderer = InitRenderer(RECTANGLE, CL_RED, CL_RED, 2);
    AddTrait(myActor, renderer);

    AddActor(myScene, myActor);

    Window* window = InitWindow("Hello, World!", 800, 600, 0, 0, myScene, NULL);
    OpenWindow(window);

    return 0;
}