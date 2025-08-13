#include "CubeInit/CubeInit.h"
#include "CubeGFX/CubeGFX.h"

void setup() {
  Serial.begin(9600);
  initCube(100);
}

void loop() {

// draw a cube with fill and outline
  drawCube(Vector3u(0, 0, 0), Vector3u(3, 3, 3), Color(0, 255, 0), Color(255, 0, 0), true, true, true);

  displayMatrix(); 
}
