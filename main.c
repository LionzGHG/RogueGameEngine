
#include "rogue.h"

void update(Scene* scene, float dt) {
    GetActor(scene, "My Actor")->transform->position.x += 50.0f * dt;
}

int main() {
    Scene* myScene = InitScene("myScene", update);

    Actor* myActor = InitActor("My Actor");

    myActor->transform->scale = Vec2(400.0f, 250.0f);

    //Trait* renderer = InitRenderer(RECTANGLE, CL_RED, CL_RED, 2);
    //AddTrait(myActor, renderer);

    LoadImage2D("example.png");
    Trait* renderer = InitPngRenderer((Image2D*)GetAsset("example.png"));
    AddTrait(myActor, renderer);

    AddActor(myScene, myActor);

    Window* window = InitWindow("Hello, World!", 800, 600, 0, 0, myScene, NULL);
    OpenWindow(window);

    return 0;
}