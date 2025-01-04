
#ifndef ROGUE_RENDER_H
#define ROGUE_RENDER_H

#include "window.h"
#include <Windows.h>

#define TR_RENDERER "Renderer"

#define CL_RED rgb(255, 0, 0)
#define CL_GREEN rgb(0, 255, 0)
#define CL_BLUE rgb(0, 0, 255)
#define CL_YELLOW rgb(255, 255, 0)
#define CL_CYAN rgb(0, 255, 255)
#define CL_MAGENTA rgb(255, 0, 255)
#define CL_WHITE rgb(255, 255, 255)
#define CL_BLACK rgb(0, 0, 0)

typedef struct Color {
    unsigned char r, g, b, a;
} Color;

typedef enum PrimitiveType {
    RECTANGLE = 0,
    CIRCLE = 1,
    TRIANGLE = 2,
} PrimitiveType;

typedef struct Primitive {
    PrimitiveType ptype;
    int x, y, width, height;
    Color fillColor;
    Color outlineColor;
    int borderWidth;
} Primitive;

typedef struct Renderer {
    Trait trait;
    PrimitiveType ptype;
    Color fillColor;
    Color borderColor;
    int borderWidth;
} Renderer;

Primitive* InitPrimitive(PrimitiveType ptype, int x, int y, int width, int height, Color fillColor, Color outlineColor, int borderWidth);
void DrawPrimitive(Window* window, Primitive* p);

Trait* InitRenderer(PrimitiveType ptype, Color fillColor, Color borderColor, int borderWidth);

Color rgb(unsigned char r, unsigned char g, unsigned char b);
Color rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

#endif