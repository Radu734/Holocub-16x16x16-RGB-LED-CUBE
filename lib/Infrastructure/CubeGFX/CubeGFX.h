#pragma once
#ifndef CUBE_GFX_H
#define CUBE_GFX_H

#include <stdint.h>
#include <Arduino.h>
#include "CubeConfig/CubeConfig.h"

/************ GFX Drawings ***************/

void drawCube(Vector3u startPoz, Vector3u endPoz, Color fillColor, Color outlineColor, bool fill, bool outline, bool fullOutlines);
//void drawSquare(Vector3u startPoz, Vector3u endPoz, Color fillColor, Color outlineColor, bool fill, bool outline);

/************ Gradients ***************/

void gradient();

/********* Infrastructure *********/
void displayMatrix();
void clearMatrix();
void setPixel(int indexInStrip, int x, int y, int z);
void changeLocationOfVoxel(int oldX, int oldY, int oldZ, int newX, int newY, int newZ);

#endif // CUBE_GFX_H