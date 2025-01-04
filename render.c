
#include <stdlib.h>
#include <stdio.h>

#include "window.h"
#include "render.h"

Color rgb(unsigned char r, unsigned char g, unsigned char b) {
    Color* rgb = (Color*)malloc(sizeof(Color));
    rgb->r = r;
    rgb->g = g;
    rgb->b = b;
    rgb->a = 1;

    return *rgb;
}

Color rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    Color* rgba = (Color*)malloc(sizeof(Color));
    rgba->r = r;
    rgba->g = g;
    rgba->b = b;
    rgba->a = a;

    return *rgba;
}

Primitive* InitPrimitive(PrimitiveType ptype, int x, int y, int width, int height, Color fillColor, Color outlineColor, int borderWidth) {
    Primitive* primitive = (Primitive*)malloc(sizeof(Primitive));

    primitive->ptype = ptype;
    primitive->x = x;
    primitive->y = y;
    primitive->width = width;
    primitive->height = height;
    primitive->fillColor = fillColor;
    primitive->outlineColor = outlineColor;
    primitive->borderWidth = borderWidth;

    return primitive;
}

void DrawPrimitive(Window* window, Primitive* p) {
    HDC hdc = GetDC(window->hwnd);

    if (hdc == NULL) {
        fprintf(stderr, "ERROR: Failed to get HDC for window.\n");
        return;
    }

    switch (p->ptype) {
        case RECTANGLE:
            HBRUSH hBrush = CreateSolidBrush(RGB(p->fillColor.r, p->fillColor.g, p->fillColor.b));
            HPEN hPen = CreatePen(PS_SOLID, p->borderWidth, RGB(p->outlineColor.r, p->outlineColor.g, p->outlineColor.b));

            HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
            HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

            Rectangle(hdc, p->x, p->y, p->x + p->width, p->y + p->height);

            SelectObject(hdc, hOldBrush);
            SelectObject(hdc, hOldPen);

            DeleteObject(hBrush);
            DeleteObject(hPen);
            break;
        default:
            fprintf(stderr, "Warning: unsupported primitive type %d\n", p->ptype);
            break;
    }

    ReleaseDC(window->hwnd, hdc);
}

Trait* InitRenderer(PrimitiveType ptype, Color fillColor, Color borderColor, int borderWidth) {
    Renderer* renderer = (Renderer*)malloc(sizeof(Renderer));

    if (!renderer) {
        fprintf(stderr, "ERROR: Memory allocation for Renderer trait failed!\n");
        exit(EXIT_FAILURE);
    }

    renderer->trait.id = TR_RENDERER;

    renderer->ptype = ptype;
    renderer->fillColor = fillColor;
    renderer->borderWidth = borderWidth;
    renderer->borderColor = borderColor;

    return (Trait*)renderer;
}