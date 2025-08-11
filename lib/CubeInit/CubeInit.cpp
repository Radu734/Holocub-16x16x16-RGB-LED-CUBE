#include "CubeConfig.h"

Adafruit_NeoPixel** strips = nullptr;
Voxel*** voxelMatrix = nullptr;
int CUBE_WIDTH = 0;
int CUBE_DEPTH = 0;
int CUBE_HEIGHT = 0;
int LED_CNT_PerLayer = 0;

// Use non matrix indexing for the size of the cube
// i.e. initCube(pins, 4, 4, 4) for a 4x4x4 cube
void initCube(const int* pins, uint8_t brightness, int cubeSizeX, int cubeSizeY, int cubeSizeZ) {
    CUBE_WIDTH = cubeSizeX;
    CUBE_DEPTH = cubeSizeY;
    CUBE_HEIGHT = cubeSizeZ;
    LED_CNT_PerLayer = CUBE_WIDTH * CUBE_DEPTH;

    // Allocate strips
    strips = new Adafruit_NeoPixel*[CUBE_HEIGHT];
    for (int i = 0; i < CUBE_HEIGHT; i++) {
        strips[i] = new Adafruit_NeoPixel(LED_CNT_PerLayer, pins[i], NEO_GRB + NEO_KHZ800);
        strips[i]->begin();
        strips[i]->setBrightness(brightness);
    }

    // Allocate voxel matrix
    voxelMatrix = new Voxel**[CUBE_WIDTH];
    for (int x = 0; x < CUBE_WIDTH; x++) {
        voxelMatrix[x] = new Voxel*[CUBE_DEPTH];
        for (int y = 0; y < CUBE_DEPTH; y++) {
            voxelMatrix[x][y] = new Voxel[CUBE_HEIGHT];
        }
    }
}