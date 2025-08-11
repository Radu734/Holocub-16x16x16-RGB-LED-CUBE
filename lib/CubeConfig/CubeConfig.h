// CubeConfig.h
#pragma once
#ifndef CUBE_CONFIG_H
#define CUBE_CONFIG_H

#include <Adafruit_NeoPixel.h>
#include "Voxel.h"

extern Adafruit_NeoPixel** strips;
extern Voxel*** voxelMatrix;
extern int CUBE_WIDTH;
extern int CUBE_DEPTH;
extern int CUBE_HEIGHT;
extern int LED_CNT_PerLayer;

#endif // CUBE_CONFIG_H