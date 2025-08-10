// CubeConfig.h
#pragma once
#ifndef CUBE_CONFIG_H
#define CUBE_CONFIG_H

#include <Adafruit_NeoPixel.h>
#include "Voxel.h"

void initCube(const int* pins, int cubeSize); // No LED count needed
extern Adafruit_NeoPixel** strips;
extern Voxel*** voxelMatrix;
extern int NUM_LAYERS;
extern int LED_CNT_PerLayer;

#endif // CUBE_CONFIG_H