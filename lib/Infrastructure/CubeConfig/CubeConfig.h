// CubeConfig.h
#ifndef CUBE_CONFIG_H
#define CUBE_CONFIG_H

#include <Adafruit_NeoPixel.h>
#include <stdint.h>
#include "CubeTypes/CubeTypes.h"

// Select your cube size here
constexpr uint16_t CUBE_WIDTH = 4;
constexpr uint16_t CUBE_DEPTH = 4;
constexpr uint16_t CUBE_HEIGHT = 4;

constexpr int LAYER_PINS[CUBE_HEIGHT] = {4, 5, 6, 7 /* fill with your pins */ };
constexpr int LED_CNT_PerLayer = CUBE_WIDTH * CUBE_DEPTH;

// Strips
extern Adafruit_NeoPixel strips[CUBE_HEIGHT];

// Voxel matrix
extern Voxel voxelMatrix[CUBE_WIDTH][CUBE_DEPTH][CUBE_HEIGHT];

#endif // CUBE_CONFIG_H