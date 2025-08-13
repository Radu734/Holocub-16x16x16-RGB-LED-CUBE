#pragma once
#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

extern uint16_t CUBE_WIDTH;
extern uint16_t CUBE_DEPTH;
extern uint16_t CUBE_HEIGHT;

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;

  Color() : r(0), g(0), b(0) {}
  Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
  
  bool operator==(const Color& other) const {
    return (r == other.r && g == other.g && b == other.b);
  }
  bool operator!=(const Color& other) const {
    return (r != other.r || g != other.g || b != other.b);
  }
};

struct Vector3u {
  uint16_t x;
  uint16_t y;
  uint16_t z;

  Vector3u() : x(0), y(0), z(0) {}
  Vector3u(uint16_t x, uint16_t y, uint16_t z) : x(x), y(y), z(z) {}

  bool operator==(const Vector3u& other) const {
    return (x == other.x && y == other.y && z == other.z);
  }
  bool operator<=(const Vector3u& other) const {
    return (x <= other.x && y <= other.y && z <= other.z);
  }
  bool operator<(const Vector3u& other) const {
    return (x < other.x && y < other.y && z < other.z);
  }
  bool operator>=(const Vector3u& other) const {
    return (x >= other.x && y >= other.y && z >= other.z);
  }
  bool operator>(const Vector3u& other) const {
    return (x > other.x && y > other.y && z > other.z);
  }
  bool operator!=(const Vector3u& other) const {
    return (x != other.x || y != other.y || z != other.z);
  }

  bool isInCubeBounds() const {
    return (x < CUBE_WIDTH && y < CUBE_DEPTH && z < CUBE_HEIGHT);
  }
};

struct Voxel {
  uint8_t r = 0, g = 0, b = 0;

  void setColor(uint8_t RED, uint8_t GREEN, uint8_t BLUE) {
    r = RED;
    g = GREEN;
    b = BLUE;
    isOn = ((r + g + b) != 0);
  }

  void setColor(Color color) {
    setColor(color.r, color.g, color.b);
  }

  Color getColor() const {
    return Color(r, g, b);
  }

  // removes all color information, but keeps the voxel in the matrix
  // combine with gradient functions
  void markAsOn() {
    isOn = true;
    r = 0;
    g = 0;
    b = 0;
  }

  // make gradients ignore this voxel
  void markAsOff() {
    isOn = false;
  }

  void turnVoxelOff() {
    r = 0;
    g = 0;
    b = 0;
    isOn = false;
  }

  bool getIsOn() {
    return isOn;
  }

  // HSV values: h = 0-359, s = 0-255, v = 0-255
  // RGB output: r, g, b = 0-255
  void setColorHSV(uint16_t h, uint8_t s, uint8_t v) {
      
    uint8_t region = h / 60;
    uint16_t remainder = (h % 60) * 255 / 60;

    uint8_t p = (v * (255 - s)) / 255;
    uint8_t q = (v * (255 - (s * remainder) / 255)) / 255;
    uint8_t t = (v * (255 - (s * (255 - remainder)) / 255)) / 255;

    switch (region) {
      case 0:
        r = v; g = t; b = p;
        break;
      case 1:
        r = q; g = v; b = p;
        break;
      case 2:
        r = p; g = v; b = t;
        break;
      case 3:
        r = p; g = q; b = v;
        break;
      case 4:
        r = t; g = p; b = v;
        break;
      default:  // case 5:
        r = v; g = p; b = q;
        break;
    }
  }

private: 
  bool isOn = false;
};

#endif // COLOR_H