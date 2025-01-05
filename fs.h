
#ifndef ROGUE_FS_H
#define ROGUE_FS_H

#include <Windows.h>
#include "core.h"
#include "assets.h"

#define TR_PNG_RENDERER "PngRenderer"

typedef struct Image2D {
    Asset asset;
    const char* path;
    const char* bitPath;
    HBITMAP bitMap;
} Image2D;

typedef struct PngRenderer {
    Trait trait;
    Image2D* image;
    Vec size;
} PngRenderer;

Trait* InitPngRenderer(Image2D* image);
void RenderPng(Actor* actor, Window* window, HDC* hdc);

Image2D* LoadImage2D(const char* path);

void BitMap(const char* pngPath, const char* bmpPath);

#endif