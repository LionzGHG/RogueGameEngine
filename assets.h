
#ifndef ROGUE_ASSETS_H
#define ROGUE_ASSETS_H

#define IMAGES_PATH "./assets/images/"
#define BITMAPS_PATH "./assets/bitMaps/"

typedef struct Asset {
    const char* name;
} Asset;

Asset* GetAsset(const char* name);
void LoadAsset(Asset* asset);  

#endif