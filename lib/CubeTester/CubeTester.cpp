#include "CubeTester.h"
#include "CubeConfig.h"

// ******** Strip-only tests ********

void testCube() {
  // static uint8_t R = random(0, 255), G = random(0, 255), B = random(0, 255);
  static int hue = 0;

  for (int i = 0; i < CUBE_HEIGHT; i++) {
    for (int j = 0; j < LED_CNT_PerLayer; j++) {
      strips[i].setPixelColor(j, strips[i].ColorHSV(hue, 255, 255));
      strips[i].show();
      delay(250);
      strips[i].clear();
      strips[i].show();
      hue = (hue + 512) % 65535; 
    }
    
    // R = (R + random(0, 100)) % 255;
    // G = (G + random(0, 100)) % 255;
    // B = (B + random(0, 100)) % 255;
  }

}
void testCollum(int col) {
  static uint8_t R = 0, G = 0, B = 0;

  for (int i = 0; i < CUBE_HEIGHT; i++) {
    strips[i].setPixelColor(col, strips[i].Color(R, G, B));
    strips[i].show();
    delay(10);
  }

  R = (R + 1) % 255;
  G = (G + 3) % 255;
  B = (B + 4) % 255;
}
