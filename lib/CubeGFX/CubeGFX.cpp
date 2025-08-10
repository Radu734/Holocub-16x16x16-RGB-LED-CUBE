#include "CubeGFX.h"
#include "CubeConfig.h"
#include <Arduino.h>


// ************ Matrix-based tests ************

void middle() {
  voxelMatrix[1][1][1].setColor(50, 0, 0);
  voxelMatrix[1][1][2].setColor(100, 0, 0);
  voxelMatrix[1][2][1].setColor(150, 0, 0);
  voxelMatrix[1][2][2].setColor(200, 0, 0);
  voxelMatrix[2][1][1].setColor(255, 0, 0);
  voxelMatrix[2][1][2].setColor(0, 0, 100);
  voxelMatrix[2][2][1].setColor(0, 0, 150);
  voxelMatrix[2][2][2].setColor(0, 0, 250);
}
// TO REFACTOR: MAKE MULTIPLE dvdPlayer CALLS POSSIBLE
void dvdPlayer(float voxelsPerSecond, uint8_t startX, uint8_t startY, uint8_t startZ) {

  static short pozitiveMovementX = 1;
  static short pozitiveMovementY = 1;
  static short pozitiveMovementZ = 1;

  static uint8_t positionZ = startZ;
  static uint8_t positionY = startY;
  static uint8_t positionX = startX;

  static uint32_t prevTime = millis();
  static uint32_t timeBetweenChangingVoxel = 1000 / voxelsPerSecond;

  static uint16_t hue = 0;

  voxelMatrix[positionX][positionY][positionZ].setColorHSV(hue, 255, 255);

  if (millis() - prevTime > timeBetweenChangingVoxel) {
    
    if (positionZ + pozitiveMovementZ >= NUM_LAYERS || positionZ + pozitiveMovementZ < 0)  pozitiveMovementZ = -pozitiveMovementZ;
    if (positionY + pozitiveMovementY >= NUM_LAYERS || positionY + pozitiveMovementY < 0)  pozitiveMovementY = -pozitiveMovementY;
    if (positionX + pozitiveMovementX >= NUM_LAYERS || positionX + pozitiveMovementX < 0)  pozitiveMovementX = -pozitiveMovementX;

    changeLocationOfVoxel(positionX, positionY, positionZ, positionX + pozitiveMovementX, positionY + pozitiveMovementY, positionZ + pozitiveMovementZ);

    positionZ += pozitiveMovementZ;
    positionY += pozitiveMovementY;
    positionX += pozitiveMovementX;

    prevTime = millis();
    hue = (hue + 25) % 65535;
  }

}
void rain(int dropsPerSecond, int voxelDropSpeedPerSecond) {
  static uint32_t dropTime = millis();
  static uint32_t spawnTime = millis();
  static uint32_t timeBetweenSpawnsMills = 1000 / dropsPerSecond;
  static uint32_t timeBetweenFallingMills = 1000 / voxelDropSpeedPerSecond;


  if (millis() - dropTime > timeBetweenFallingMills) {
    
    // delete bottom layer
    for (int x = 0; x < NUM_LAYERS; x++) {
      for (int y = 0; y < NUM_LAYERS; y++) {
        voxelMatrix[x][y][0].markAsOff();
      }
    }

    // do not check bottom layer
    for (int z = 1; z < NUM_LAYERS; z++) {
      for (int x = 0; x < NUM_LAYERS; x++) {
        for (int y = 0; y < NUM_LAYERS; y++) {
          if (voxelMatrix[x][y][z].getIsOn() == true) {
            // apply falling one layer
            changeLocationOfVoxel(x, y, z, x, y, z - 1);
          }
        }
      }
    }

    dropTime = millis();
  }

  if (millis() - spawnTime >= timeBetweenSpawnsMills) {

    // top of the cube
    voxelMatrix[random(0, NUM_LAYERS)][random(0, NUM_LAYERS)][NUM_LAYERS - 1].markAsOn();

    spawnTime = millis();
  }

} 
// TO REFACTOR: make it scalable for sizes bigger than 4x4x4
void makeWave(int voxelsPerSecond, int startingLayer, uint8_t r, uint8_t g, uint8_t b, uint16_t chosenVoxels2D) {

  if (startingLayer >= NUM_LAYERS || NUM_LAYERS != 4) {
    return; // only works for 4x4x4 bc of the fixed bitset size of 16 bits
  }

  
}

// ******** Strip-only tests ********

void testCube() {
  static uint8_t R = 0, G = 0, B = 0;

  for (int i = 0; i < NUM_LAYERS; i++) {
    for (int j = 0; j < LED_CNT_PerLayer; j++) {
      strips[i]->setPixelColor(j, strips[i]->Color(R, G, B));
      strips[i]->show();
      delay(250);
      strips[i]->clear();
      strips[i]->show();
    }
  }

  R = (R + 1) % 255;
  G = (G + 3) % 255;
  B = (B + 4) % 255;
}
void testCollum(int col) {
  static uint8_t R = 0, G = 0, B = 0;

  for (int i = 0; i < NUM_LAYERS; i++) {
    strips[i]->setPixelColor(col, strips[i]->Color(R, G, B));
    strips[i]->show();
    delay(10);
  }

  R = (R + 1) % 255;
  G = (G + 3) % 255;
  B = (B + 4) % 255;
}

// ******** Infrastructure ********
void gradient() {
  const uint8_t MAX_COLOR = 255;
  const int SIZE = 4; // adjust if your cube is larger

  for (int z = 0; z < SIZE; z++) {
    // Compute gradient value for this Z-layer
    uint8_t value = map(z, 0, SIZE - 1, 0, MAX_COLOR);

    for (int y = 0; y < SIZE; y++) {
      for (int x = 0; x < SIZE; x++) {
        if (voxelMatrix[x][y][z].getIsOn()) {
          // Example gradient: blue fades into red going up
          voxelMatrix[x][y][z].setColor(value, 0, MAX_COLOR - value);
        }
      }
    }
  }

}
void setPixel(int indexInStrip, int x, int y, int z) {
  strips[z]->setPixelColor(indexInStrip,
    strips[z]->Color(voxelMatrix[x][y][z].r,
                     voxelMatrix[x][y][z].g,
                     voxelMatrix[x][y][z].b));
}
void displayMatrix() {
  for (int z = 0; z < NUM_LAYERS; z++) {
    strips[z]->clear(); // Clear before drawing new frame

    for (int y = 0; y < NUM_LAYERS; y++) {
      for (int x = 0; x < NUM_LAYERS; x++) {
        int index;
        if (y % 2 == 0) {
          index = y * 4 + x;
        } else {
          index = y * 4 + (NUM_LAYERS - 1 - x);
        }

        setPixel(index, x, y, z);
      }
    }

    strips[z]->show();
  }
}
void changeLocationOfVoxel(int oldX, int oldY, int oldZ, int newX, int newY, int newZ) {
  voxelMatrix[newX][newY][newZ].setColor(voxelMatrix[oldX][oldY][oldZ].r, voxelMatrix[oldX][oldY][oldZ].g, voxelMatrix[oldX][oldY][oldZ].b);
  voxelMatrix[oldX][oldY][oldZ].setColor(0, 0, 0);
}
void clearVoxelMatrix() {

  for (int z = 0; z < NUM_LAYERS; z++) {
    for (int y = 0; y < NUM_LAYERS; y++) {
      for (int x = 0; x < NUM_LAYERS; x++) {
        voxelMatrix[x][y][z].setColor(0, 0, 0);
      }
    }
  }
}
void initialiseLayers(uint8_t brightness) {
    for (int i = 0; i < NUM_LAYERS; i++) {
        strips[i]->begin();
        strips[i]->setBrightness(brightness);
        strips[i]->clear();
        strips[i]->show(); // Ensure all are initially off
    }
}
