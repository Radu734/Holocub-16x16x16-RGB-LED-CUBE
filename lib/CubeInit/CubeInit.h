#pragma once
#ifndef CUBE_INIT_H
#define CUBE_INIT_H

#include <Adafruit_NeoPixel.h>
#include "CubeConfig.h"
#include "Voxel.h"

Adafruit_NeoPixel strips[CUBE_HEIGHT] = {
    Adafruit_NeoPixel(LED_CNT_PerLayer, LAYER_PINS[0], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(LED_CNT_PerLayer, LAYER_PINS[1], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(LED_CNT_PerLayer, LAYER_PINS[2], NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(LED_CNT_PerLayer, LAYER_PINS[3], NEO_GRB + NEO_KHZ800)
};

Voxel voxelMatrix[CUBE_WIDTH][CUBE_DEPTH][CUBE_HEIGHT];

inline void initCube(uint8_t brightness) {
    for (int i = 0; i < CUBE_HEIGHT; i++) {
        strips[i].begin();
        strips[i].setBrightness(brightness);
        strips[i].clear(); 
        strips[i].show(); // clear LEDs
    }
}

#endif // CUBE_INIT_H