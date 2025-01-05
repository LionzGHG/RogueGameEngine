
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>

LARGE_INTEGER frequency, startTime, currentTime;

void InitTimer() {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&startTime);
}

float GetTime() {
    QueryPerformanceCounter(&currentTime);
    return (float)(currentTime.QuadPart - startTime.QuadPart) / (float)frequency.QuadPart;
}