#pragma once
#ifndef CUBE_GFX_H
#define CUBE_GFX_H

#include <stdint.h>
#include <Arduino.h>
#include "CubeConfig.h"


/********* Infrastructure *********/
void gradient();
void setPixel(int indexInStrip, int x, int y, int z);
void displayMatrix();
void changeLocationOfVoxel(int oldX, int oldY, int oldZ, int newX, int newY, int newZ);
void clearMatrix();
bool loadVoxelRaw(const char *filename);

#endif // CUBE_GFX_H