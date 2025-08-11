#include "Rain.h"
#include "CubeGFX.h"

void rain(int dropsPerSecond, int voxelDropSpeedPerSecond) {
  static uint32_t dropTime = millis();
  static uint32_t spawnTime = millis();
  static uint32_t timeBetweenSpawnsMills = 1000 / dropsPerSecond;
  static uint32_t timeBetweenFallingMills = 1000 / voxelDropSpeedPerSecond;


  if (millis() - dropTime > timeBetweenFallingMills) {
    
    // delete bottom layer
    for (int x = 0; x < CUBE_WIDTH; x++) {
      for (int y = 0; y < CUBE_DEPTH; y++) {
        voxelMatrix[x][y][0].markAsOff();
      }
    }

    // do not check bottom layer
    for (int z = 1; z < CUBE_HEIGHT; z++) {
      for (int x = 0; x < CUBE_WIDTH; x++) {
        for (int y = 0; y < CUBE_DEPTH; y++) {
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
    voxelMatrix[random(0, CUBE_WIDTH)][random(0, CUBE_DEPTH)][CUBE_HEIGHT - 1].markAsOn();

    spawnTime = millis();
  }

} 
