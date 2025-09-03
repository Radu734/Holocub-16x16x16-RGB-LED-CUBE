#include <Arduino.h>
#include "CubeInit.h"
#include "Rain/Rain.h"
#include "CubeGFX.h"

void setup() {
  initCube(100);
}

void loop() {
  rain(40, 6);
  gradient();
  displayMatrix();
  delay(10);
}
