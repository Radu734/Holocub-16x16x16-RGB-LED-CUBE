#include "CubeConfig.h"

Adafruit_NeoPixel** strips = nullptr;
Voxel*** voxelMatrix = nullptr;
int NUM_LAYERS = 0;
int LED_CNT_PerLayer = 0;

void initCube(const int* pins, int cubeSize) {
    NUM_LAYERS = cubeSize;
    LED_CNT_PerLayer = cubeSize * cubeSize; // auto calc

    // Allocate strips
    strips = new Adafruit_NeoPixel*[NUM_LAYERS];
    for (int i = 0; i < NUM_LAYERS; i++) {
        strips[i] = new Adafruit_NeoPixel(LED_CNT_PerLayer, pins[i], NEO_GRB + NEO_KHZ800);
        strips[i]->begin();
        strips[i]->setBrightness(50);
    }

    // Allocate voxel matrix
    voxelMatrix = new Voxel**[NUM_LAYERS];
    for (int x = 0; x < NUM_LAYERS; x++) {
        voxelMatrix[x] = new Voxel*[NUM_LAYERS];
        for (int y = 0; y < NUM_LAYERS; y++) {
            voxelMatrix[x][y] = new Voxel[NUM_LAYERS];
        }
    }
}