#include "DvdPlayer.h"

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
    
    if (positionZ + pozitiveMovementZ >= CUBE_HEIGHT || positionZ + pozitiveMovementZ < 0)  pozitiveMovementZ = -pozitiveMovementZ;
    if (positionY + pozitiveMovementY >= CUBE_DEPTH || positionY + pozitiveMovementY < 0)  pozitiveMovementY = -pozitiveMovementY;
    if (positionX + pozitiveMovementX >= CUBE_WIDTH || positionX + pozitiveMovementX < 0)  pozitiveMovementX = -pozitiveMovementX;

    changeLocationOfVoxel(positionX, positionY, positionZ, positionX + pozitiveMovementX, positionY + pozitiveMovementY, positionZ + pozitiveMovementZ);

    positionZ += pozitiveMovementZ;
    positionY += pozitiveMovementY;
    positionX += pozitiveMovementX;

    prevTime = millis();
    hue = (hue + 25) % 65535;
  }

}
