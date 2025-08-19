#include "CubeGFX.h"
#include <SD.h>

// ******** Infrastructure ********
// applies a gradient effect to the led's marked as "on" in the voxelMatrix
void gradient() {
  const uint8_t MAX_COLOR = 255;

  for (int z = 0; z < CUBE_HEIGHT; z++) {
    // Compute gradient value for this Z-layer
    uint8_t value = map(z, 0, CUBE_HEIGHT - 1, 0, MAX_COLOR);

    for (int y = 0; y < CUBE_DEPTH; y++) {
      for (int x = 0; x < CUBE_WIDTH; x++) {
        if (voxelMatrix[x][y][z].getIsOn()) {
          // Example gradient: blue fades into red going up
          voxelMatrix[x][y][z].setColor(value, 0, MAX_COLOR - value);
        }
      }
    }
  }

}
void setPixel(int indexInStrip, int x, int y, int z) {
  strips[z].setPixelColor(indexInStrip,
    strips[z].Color(voxelMatrix[x][y][z].r,
                     voxelMatrix[x][y][z].g,
                     voxelMatrix[x][y][z].b));
}
void displayMatrix() {
  for (int z = 0; z < CUBE_HEIGHT; z++) {
    strips[z].clear(); // Clear before drawing new frame

    for (int y = 0; y < CUBE_DEPTH; y++) {
      for (int x = 0; x < CUBE_WIDTH; x++) {
        int index;
        if (y % 2 == 0) {
          index = y * 4 + x;
        } else {
          index = y * 4 + (CUBE_WIDTH - 1 - x);
        }

        setPixel(index, x, y, z);
      }
    }

    strips[z].show();
  }
}
void changeLocationOfVoxel(int oldX, int oldY, int oldZ, int newX, int newY, int newZ) {
  voxelMatrix[newX][newY][newZ].setColor(voxelMatrix[oldX][oldY][oldZ].r, voxelMatrix[oldX][oldY][oldZ].g, voxelMatrix[oldX][oldY][oldZ].b);
  voxelMatrix[oldX][oldY][oldZ].setColor(0, 0, 0);
}
void clearMatrix() {
  for (int z = 0; z < CUBE_HEIGHT; z++) {
    for (int y = 0; y < CUBE_DEPTH; y++) {
      for (int x = 0; x < CUBE_WIDTH; x++) {
        voxelMatrix[x][y][z].setColor(0, 0, 0);
      }
    }
  }
}
bool loadVoxelRaw(const char *filename) {
  File file = SD.open(filename, FILE_READ);
  if (!file) {
    Serial.println("Failed to open file!");
    return false;
  }

  size_t expectedSize = (size_t)CUBE_WIDTH * CUBE_DEPTH * CUBE_HEIGHT * 3;
  if (file.size() < expectedSize) {
    Serial.println("File too short!");
    file.close();
    return false;
  }

  for (int z = 0; z < CUBE_HEIGHT; z++) {
    for (int y = 0; y < CUBE_DEPTH; y++) {
      for (int x = 0; x < CUBE_WIDTH; x++) {
        voxelMatrix[x][y][z].r = file.read(); // 1 byte
        voxelMatrix[x][y][z].g = file.read(); // 1 byte
        voxelMatrix[x][y][z].b = file.read(); // 1 byte
      }
    }
  }

  file.close();
  return true;
}
