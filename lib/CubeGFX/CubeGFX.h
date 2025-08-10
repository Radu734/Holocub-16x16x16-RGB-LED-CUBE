#pragma once
#ifndef CUBE_GFX_H
#define CUBE_GFX_H

#include <stdint.h>

// ************ Matrix-based tests ************

// TO REFACTOR: MAKE MULTIPLE dvdPlayer CALLS POSSIBLE OR ADD RANDOM DEVIATION IN MOVEMENT
void dvdPlayer(float voxelsPerSecond, uint8_t startX, uint8_t startY, uint8_t startZ);
void middle();
void rain(int dropsPerSecond, int voxelDropSpeedPerSecond);

// TO REFACTOR: make it scalable for sizes bigger than 4x4x4
void makeWave(int voxelsPerSecond, int startingLayer, uint8_t r, uint8_t g, uint8_t b, uint16_t chosenVoxels2D);

// ******** Strip-only tests ********

void testCube();
void testCollum(int col);

// ******** Infrastructure ********
void gradient();
void setPixel(int indexInStrip, int x, int y, int z);
void displayMatrix();
void changeLocationOfVoxel(int oldX, int oldY, int oldZ, int newX, int newY, int newZ);
void clearVoxelMatrix();
void initialiseLayers(uint8_t brightness);

#endif // CUBE_GFX_H