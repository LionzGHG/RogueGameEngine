
#include "assets.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

Asset* ASSETS = NULL;
int assetCount = 0;

void LoadAsset(Asset* asset) {
    Asset** newAssets = (Asset**)realloc(ASSETS, sizeof(Asset*) * (ASSETS ? assetCount + 1 : 1));
    if (newAssets == NULL) {
        fprintf(stderr, "Failed to allocate memory for new Asset!\n");
        exit(EXIT_FAILURE);
    }

    newAssets[assetCount] = asset;
    ASSETS = *newAssets;
    assetCount++;
}

Asset* GetAsset(const char* name) {
    for (int i = 0; i < assetCount; i++) {
        Asset* asset = &ASSETS[i];
        if (strcmp(asset->name, name) == 0) {
            return asset;
        }
    }

    //WIN32_FIND_DATA findFileData;
    //HANDLE hFind = INVALID_HANDLE_VALUE;

    //char searchPattern[MAX_PATH];
    //snprintf(searchPattern, sizeof(searchPattern), "%s\\*.*", IMAGES_PATH);

    //hFind = FindFirstFile(searchPattern, &findFileData);

    //if (hFind == INVALID_HANDLE_VALUE) {
    //    fprintf(stderr, "The images asset-path was obstructed or deleted!\n");
    //    exit(EXIT_FAILURE);
    //}

    //do {
    //    if (strcmp(findFileData.cFileName, name) == 0) {
    //        FindClose(hFind);
    //        // return the asset here
    //    }
    //} while (FindNextFile(hFind, &findFileData) != 0);

    //FindClose(hFind);
    fprintf(stderr, "ERROR: No asset with the name %s found!\n", name);
    exit(EXIT_FAILURE);
}