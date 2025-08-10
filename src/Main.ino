#include "CubeConfig.h"
#include "CubeGFX.h"

constexpr int cubePins[] = {4, 5, 6, 7};
constexpr int cubeSize = 4;

void setup() {
  initCube(cubePins, cubeSize);
}

void loop() {
  middle();
  dvdPlayer(1.0f, 1, 0, 0);
  displayMatrix();
}
