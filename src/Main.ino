#include "CubeConfig.h"
#include "CubeInit.h"
#include "CubeGFX.h"

constexpr int cubePins[] = {4, 5, 6, 7};

void setup() {
  initCube(cubePins, 4, 4, 4);
}

void loop() {
  dvdPlayer(1.0f, 1, 0, 0);
  displayMatrix();
}
