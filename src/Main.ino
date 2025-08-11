#include "CubeInit.h"
#include "CubeGFX.h"
#include "DvdPlayer/DvdPlayer.h"

void setup() {
  Serial.begin(9600);
  initCube(100);
}

void loop() {
  dvdPlayer(2, 0, 1, 1);
  //gradient(); // Uncomment to see the gradient effect
  displayMatrix(); 
}
