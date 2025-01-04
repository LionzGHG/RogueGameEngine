
#ifndef ROGUE_WINDOW_H
#define ROGUE_WINDOW_H

#include <Windows.h>
#include <stddef.h>

#include "core.h"

typedef struct Scene Scene;

typedef struct Window {
    const char* title;
    int width;
    int height;
    int x;
    int y;
    Scene* activeScene;

    void* parent;
    HWND hwnd;
    WNDCLASS wc;
} Window;

Window* InitWindow(const char* title, int width, int height, int x, int y, Scene* activeScene, Window* parent);
void OpenWindow(Window* window);
void DestroyRWindow(Window* window);

#endif