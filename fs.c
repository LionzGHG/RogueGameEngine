
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "fs.h"
#include "assets.h"

#include <stdio.h>
#include <stdlib.h>


Trait* InitPngRenderer(Image2D* image) {
    PngRenderer* renderer = (PngRenderer*)malloc(sizeof(PngRenderer));
    renderer->image = image;
    renderer->trait.id = TR_PNG_RENDERER;
    renderer->size = Vec2(0.0f, 0.0f);

    return (Trait*)renderer;
}

void RenderPng(Actor* actor, Window* window, HDC* hdc) {
    PngRenderer* renderer = (PngRenderer*)GetTrait(actor, TR_PNG_RENDERER);
    HBITMAP bitMap = renderer->image->bitMap;

    HDC hdcMem = CreateCompatibleDC(*hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, bitMap);

    BITMAP newBitMap;
    GetObject(bitMap, sizeof(BITMAP), &newBitMap);

    BitBlt(
        *hdc, 
        actor->transform->position.x, 
        actor->transform->position.y, 
        newBitMap.bmWidth, 
        newBitMap.bmHeight, 
        hdcMem, 
        0, 
        0, 
        SRCCOPY
    );

    SelectObject(hdcMem, hOldBitmap);
    DeleteDC(hdcMem);
}

Image2D* LoadImage2D(const char* path) {
    Image2D* image = (Image2D*)malloc(sizeof(Image2D));
    
    image->asset.name = path;

    char assetPath[MAX_PATH] = IMAGES_PATH;
    char bitPath[MAX_PATH] = BITMAPS_PATH;

    strcat(assetPath, path);
    
    char strCpy[MAX_PATH];
    strcpy(strCpy, path);

    char* token = strtok(strCpy, ".");
    if (token != NULL) {
        strcat(bitPath, token);
        strcat(bitPath, ".bmp");
    }

    BitMap(assetPath, bitPath);

    image->path = _strdup(assetPath);
    image->bitPath = _strdup(bitPath);

    HBITMAP bitMap = (HBITMAP)LoadImage(
        NULL,
        image->bitPath,
        IMAGE_BITMAP,
        0,
        0,
        LR_LOADFROMFILE
    );

    if (bitMap == NULL) {
        DWORD error = GetLastError();
        fprintf(stderr, "Failed to load image: %s (Error: %lu)\n", image->bitPath, error);
        exit(EXIT_FAILURE);
    }

    image->bitMap = bitMap;
    
    LoadAsset((Asset*)image);
    return image;
}

void BitMap(const char* pngPath, const char* bmpPath) {
    int width, height, channels;
    unsigned char* imgData = stbi_load(pngPath, &width, &height, &channels, 3);

    if (imgData == NULL) {
        printf("Failed to load image: %s\n", pngPath);
        return;
    }

    int result = stbi_write_bmp(bmpPath, width, height, 3, imgData);
    if (!result) {
        printf("Failed to save BMP image: %s\n", bmpPath);
    }

    stbi_image_free(imgData);
}