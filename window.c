
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

#include "window.h"
#include "render.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            DestroyRWindow(window);

            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            if (!window) {
                fprintf(stderr, "ERROR: Window pointer is NULL.\n");
                break;
            }

            if (window->activeScene->actors != NULL) {
                for (size_t i = 0; i < window->activeScene->numActors; ++i) {
                    Actor* actor = &window->activeScene->actors[i];

                    if (actor->traits != NULL) {
                        for (size_t j = 0; j < actor->numTraits; ++j) {
                            Trait* trait = &actor->traits[j];

                            if (strcmp(trait->id, TR_RENDERER) == 0) {
                                Renderer* renderer = (Renderer*)trait;

                                switch (renderer->ptype) {
                                    case RECTANGLE:
                                        Primitive* rect = InitPrimitive(
                                            RECTANGLE, 
                                            actor->transform->position.x, 
                                            actor->transform->position.y, 
                                            actor->transform->scale.x, 
                                            actor->transform->scale.y, 
                                            renderer->fillColor,
                                            renderer->borderColor,
                                            renderer->borderWidth
                                        );

                                        DrawPrimitive(window, rect);
                                        free(rect);
                                        break;
                                    default:
                                        printf("WARNING: Currently unsupported primitive type %d.\n", renderer->ptype);
                                        break;
                                }
                            }
                        }
                    } else {
                        printf("No Traits for Actor %s!\n", actor->id);
                    }
                }
            } else {
                printf("No Actors!\n");
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
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_QUIT) {
            break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void DestroyRWindow(Window* window) {
    DestroyScene(window->activeScene);
    DestroyWindow(window->hwnd);
    DestroyRWindow(window->parent);
    free(window->title);
    free(window);
}