
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

#include "window.h"
#include "render.h"
#include "fs.h"
#include "util.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

            if (!window) {
               fprintf(stderr, "ERROR: Window pointer is NULL.\n");
               exit(EXIT_FAILURE);
            }

            if (window->activeScene->actors != NULL) {
                for (size_t i = 0; i < window->activeScene->numActors; ++i) {
                    Actor* actor = &window->activeScene->actors[i];

                    if (actor->traits != NULL) {
                        for (size_t j = 0; j < actor->numTraits; ++j) {
                            Trait* trait = &actor->traits[j];

                            if (strcmp(trait->id, TR_RENDERER) == 0) 
                                Render(actor, window);

                            if (strcmp(trait->id, TR_PNG_RENDERER) == 0) 
                                RenderPng(actor, window, &hdc);
                        }
                    }
                }
            }
            
            EndPaint(hwnd, &ps);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

Window* InitWindow(const char* title, int width, int height, int x, int y, Scene* activeScene, Window* parent) {
    Window* window = (Window*)malloc(sizeof(Window));
    
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "Window";

    if (!RegisterClass(&wc)) {
        fprintf(stderr, "Failed to register window class\n");
        exit(EXIT_FAILURE);
    }
    
    HWND hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        title,
        WS_OVERLAPPEDWINDOW,
        x,
        y,
        width,
        height,
        parent ? parent->hwnd : NULL,
        NULL,
        wc.hInstance,
        NULL
    );

    if (hwnd == NULL) {
        fprintf(stderr, "Failed to create window\n");
        exit(EXIT_FAILURE);
    }

    window->title = title;
    window->parent = parent;
    window->width = width;
    window->height = height;
    window->x = x;
    window->y = y;
    window->activeScene = activeScene;
    window->parent = parent;
    window->hwnd = hwnd;
    window->wc = wc;
    
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
    return window;
}

void OpenWindow(Window* window) {
    ShowWindow(window->hwnd, SW_SHOW);

    MSG msg = {0};
    
    InitTimer();
    float lastTime = GetTime();
    float accumulator = 0.0f;
    const float maxDeltaTime = 0.1f;
    const float fixedTimeStep = 1.0f / 60.0f; // semi-fixed updates (60 FPS)

    while (1) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        float currentTime = GetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (deltaTime > maxDeltaTime) deltaTime = maxDeltaTime;

        accumulator += deltaTime;
        
        while (accumulator >= fixedTimeStep) {
            window->activeScene->update(window->activeScene, fixedTimeStep);
            accumulator -= fixedTimeStep;
        }

        InvalidateRect(window->hwnd, NULL, FALSE);
    }
}

void DestroyRWindow(Window* window) {
    DestroyScene(window->activeScene);
    DestroyWindow(window->hwnd);
    DestroyRWindow(window->parent);
    free(window->title);
    free(window);
}