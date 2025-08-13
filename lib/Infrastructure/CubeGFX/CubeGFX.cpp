#include "CubeGFX.h"

/************ GFX Drawings ***************/

// if the color is full black (0, 0, 0) and the fill boolean for that part is true, then a gradient can be applied to the voxelMatrix
// the square will be drawn from start poz to end poz, start poz has to be smaller than end poz, otherwise it will not draw anything
// the borders of the square will be considered as outlines, if the outline boolean is not set, the fill will cover the whole square
// full outlines means all of the faces will have the outline fill, else only the outer edges will be filled
void drawCube(Vector3u startPoz, Vector3u endPoz, Color fillColor, Color outlineColor, bool fill, bool outline, bool fullOutlines) {

  if (!startPoz.isInCubeBounds() || !endPoz.isInCubeBounds() || startPoz >= endPoz) {
    return; // Out of bounds
  }

  if (fill == true) {
    if (fillColor != Color(0, 0, 0)) {

      // Fill the cube with the fill color
      for (int z = startPoz.z; z <= endPoz.z; z++) {
        for (int y = startPoz.y; y <= endPoz.y; y++) {
          for (int x = startPoz.x; x <= endPoz.x; x++) {
            voxelMatrix[x][y][z].setColor(fillColor);
          }
        }
      }
    }
    else {
      
      for (int z = startPoz.z; z <= endPoz.z; z++) {
        for (int y = startPoz.y; y <= endPoz.y; y++) {
          for (int x = startPoz.x; x <= endPoz.x; x++) {
            voxelMatrix[x][y][z].markAsOn(); // Mark as on for gradient
          }
        }
      }
    }
  }

  // ovrride fill borders with outline color
  if (outline == true) {
    if (outlineColor != Color(0, 0, 0)) {
      if (fullOutlines == true) {
        // cover the outer faces with the outline

        // bottom and top faces
        for (int x = startPoz.x; x <= endPoz.x; x++) {
          for (int y = startPoz.y; y <= endPoz.y; y++) {
            voxelMatrix[x][y][startPoz.z].setColor(outlineColor); // Bottom face
            voxelMatrix[x][y][endPoz.z].setColor(outlineColor); // Top face
          }
        }

        // left and right faces
        for (int z = startPoz.z; z <= endPoz.z; z++) {
          for (int y = startPoz.y; y <= endPoz.y; y++) {
            voxelMatrix[startPoz.x][y][z].setColor(outlineColor); // Left face
            voxelMatrix[endPoz.x][y][z].setColor(outlineColor); // Right face
          }
        }

        // front and back faces
        for (int z = startPoz.z; z <= endPoz.z; z++) {
          for (int x = startPoz.x; x <= endPoz.x; x++) {
            voxelMatrix[x][startPoz.y][z].setColor(outlineColor); // Front face
            voxelMatrix[x][endPoz.y][z].setColor(outlineColor); // Back face
          }
        }
      }
      else {
        // cover the outer edges with the outline

        // bottom & top, left & right edges
        for (int x = startPoz.x; x <= endPoz.x; x++) {
          voxelMatrix[x][startPoz.y][startPoz.z].setColor(outlineColor); // Left edge
          voxelMatrix[x][endPoz.y][startPoz.z].setColor(outlineColor); // Right edge
          voxelMatrix[x][startPoz.y][endPoz.z].setColor(outlineColor); // Left edge
          voxelMatrix[x][endPoz.y][endPoz.z].setColor(outlineColor); // Right edge
        }

        // bottom & top, front & back edges
        for (int y = startPoz.y; y <= endPoz.y; y++) {
          voxelMatrix[startPoz.x][y][startPoz.z].setColor(outlineColor); // Front edge
          voxelMatrix[endPoz.x][y][startPoz.z].setColor(outlineColor); // Back edge
          voxelMatrix[startPoz.x][y][endPoz.z].setColor(outlineColor); // Front edge
          voxelMatrix[endPoz.x][y][endPoz.z].setColor(outlineColor); // Back edge
        }

        // left & right, left & right edges
        for (int z = startPoz.z; z <= endPoz.z; z++) {
          voxelMatrix[startPoz.x][startPoz.y][z].setColor(outlineColor); // Left edge
          voxelMatrix[endPoz.x][startPoz.y][z].setColor(outlineColor); // Right edge
          voxelMatrix[startPoz.x][endPoz.y][z].setColor(outlineColor); // Left edge
          voxelMatrix[endPoz.x][endPoz.y][z].setColor(outlineColor); // Right edge
        }

        // left & right, front & back edges
        for (int z = startPoz.z; z <= endPoz.z; z++) {
          voxelMatrix[startPoz.x][startPoz.y][z].setColor(outlineColor); // Front edge
          voxelMatrix[endPoz.x][startPoz.y][z].setColor(outlineColor); // Back edge
          voxelMatrix[startPoz.x][endPoz.y][z].setColor(outlineColor); // Front edge
          voxelMatrix[endPoz.x][endPoz.y][z].setColor(outlineColor); // Back edge
        }

        // front & back, left & right edges
        for (int y = startPoz.y; y <= endPoz.y; y++) {
          voxelMatrix[startPoz.x][y][startPoz.z].setColor(outlineColor); // Left edge
          voxelMatrix[endPoz.x][y][startPoz.z].setColor(outlineColor); // Right edge
          voxelMatrix[startPoz.x][y][endPoz.z].setColor(outlineColor); // Left edge
          voxelMatrix[endPoz.x][y][endPoz.z].setColor(outlineColor); // Right edge
        }

        // front & back, front & back edges
        for (int x = startPoz.x; x <= endPoz.x; x++) {
          voxelMatrix[x][startPoz.y][startPoz.z].setColor(outlineColor); // Front edge
          voxelMatrix[x][endPoz.y][startPoz.z].setColor(outlineColor); // Back edge
          voxelMatrix[x][startPoz.y][endPoz.z].setColor(outlineColor); // Front edge
          voxelMatrix[x][endPoz.y][endPoz.z].setColor(outlineColor); // Back edge
        }
      }
    }
    else {
      if (fullOutlines == true) {
        // cover the outer faces with the outline

        // bottom and top faces
        for (int x = startPoz.x; x <= endPoz.x; x++) {
          for (int y = startPoz.y; y <= endPoz.y; y++) {
            voxelMatrix[x][y][startPoz.z].markAsOn(); // Bottom face
            voxelMatrix[x][y][endPoz.z].markAsOn(); // Top face
          }
        }

        // left and right faces
        for (int z = startPoz.z; z <= endPoz.z; z++) {
          for (int y = startPoz.y; y <= endPoz.y; y++) {
            voxelMatrix[startPoz.x][y][z].markAsOn(); // Left face
            voxelMatrix[endPoz.x][y][z].markAsOn(); // Right face
          }
        }

        // front and back faces
        for (int z = startPoz.z; z <= endPoz.z; z++) {
          for (int x = startPoz.x; x <= endPoz.x; x++) {
            voxelMatrix[x][startPoz.y][z].markAsOn(); // Front face
            voxelMatrix[x][endPoz.y][z].markAsOn(); // Back face
          }
        }
      }
      else {
        // cover the outer edges with the outline

        // bottom & top, left & right edges
        for (int x = startPoz.x; x <= endPoz.x; x++) {
          voxelMatrix[x][startPoz.y][startPoz.z].markAsOn(); // Left edge
          voxelMatrix[x][endPoz.y][startPoz.z].markAsOn(); // Right edge
          voxelMatrix[x][startPoz.y][endPoz.z].markAsOn(); // Left edge
          voxelMatrix[x][endPoz.y][endPoz.z].markAsOn(); // Right edge
        }

        // bottom & top, front & back edges
        for (int y = startPoz.y; y <= endPoz.y; y++) {
          voxelMatrix[startPoz.x][y][startPoz.z].markAsOn(); // Front edge
          voxelMatrix[endPoz.x][y][startPoz.z].markAsOn(); // Back edge
          voxelMatrix[startPoz.x][y][endPoz.z].markAsOn(); // Front edge
          voxelMatrix[endPoz.x][y][endPoz.z].markAsOn(); // Back edge
        }

        // left & right, left & right edges
        for (int z = startPoz.z; z <= endPoz.z; z++) {
          voxelMatrix[startPoz.x][startPoz.y][z].markAsOn(); // Left edge
          voxelMatrix[endPoz.x][startPoz.y][z].markAsOn(); // Right edge
          voxelMatrix[startPoz.x][endPoz.y][z].markAsOn(); // Left edge
          voxelMatrix[endPoz.x][endPoz.y][z].markAsOn(); // Right edge
        }

        // left & right, front & back edges
        for (int z = startPoz.z; z <= endPoz.z; z++) {
          voxelMatrix[startPoz.x][startPoz.y][z].markAsOn(); // Front edge
          voxelMatrix[endPoz.x][startPoz.y][z].markAsOn(); // Back edge
          voxelMatrix[startPoz.x][endPoz.y][z].markAsOn(); // Front edge
          voxelMatrix[endPoz.x][endPoz.y][z].markAsOn(); // Back edge
        }

        // front & back, left & right edges
        for (int y = startPoz.y; y <= endPoz.y; y++) {
          voxelMatrix[startPoz.x][y][startPoz.z].markAsOn(); // Left edge
          voxelMatrix[endPoz.x][y][startPoz.z].markAsOn(); // Right edge
          voxelMatrix[startPoz.x][y][endPoz.z].markAsOn(); // Left edge
          voxelMatrix[endPoz.x][y][endPoz.z].markAsOn(); // Right edge
        }

        // front & back, front & back edges
        for (int x = startPoz.x; x <= endPoz.x; x++) {
          voxelMatrix[x][startPoz.y][startPoz.z].markAsOn(); // Front edge
          voxelMatrix[x][endPoz.y][startPoz.z].markAsOn(); // Back edge
          voxelMatrix[x][startPoz.y][endPoz.z].markAsOn(); // Front edge
          voxelMatrix[x][endPoz.y][endPoz.z].markAsOn(); // Back edge
        }
      }
    }
  }
}

/*
void drawSquare(Vector3u startPoz, Vector3u endPoz, Color fillColor, Color outlineColor, bool fill, bool outline) {
  
  if (!startPoz.isInCubeBounds() || !endPoz.isInCubeBounds() || startPoz >= endPoz) {
    return; // Out of bounds
  }

  // Change needed: FEAT #1 - Draw square diagonally
  // needs a line drawing algorithm to draw the square diagonally
  // create a draw line function and call it here - it will work for both fill and outline, but has the possibility to be slow
}
*/

/************ Gradients ***************/

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

// ******** Infrastructure ********

// this function sets the pixel color on the provided index in the strip based on the coordinates given for the voxelMatrix
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
