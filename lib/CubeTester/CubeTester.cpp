#include "CubeTester.h"
#include "CubeConfig.h"

// ******** Strip-only tests ********

void testCube() {
  static uint8_t R = 0, G = 0, B = 0;

  for (int i = 0; i < CUBE_HEIGHT; i++) {
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

  for (int i = 0; i < CUBE_HEIGHT; i++) {
    strips[i]->setPixelColor(col, strips[i]->Color(R, G, B));
    strips[i]->show();
    delay(10);
  }

  R = (R + 1) % 255;
  G = (G + 3) % 255;
  B = (B + 4) % 255;
}
