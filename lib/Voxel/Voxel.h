#pragma once
#ifndef VOXEL_H
#define VOXEL_H

#include <stdint.h>

struct Voxel {
    uint8_t r = 0, g = 0, b = 0;

    void setColor(uint8_t RED, uint8_t GREEN, uint8_t BLUE) {
        r = RED;
        g = GREEN;
        b = BLUE;
        isOn = ((r + g + b) != 0);
    }

    // combine with gradient functions
    void markAsOn() {
        isOn = true;    
    }
    // combine with gradient functions
    void markAsOff() {
        isOn = false;
        r = 0;
        g = 0;
        b = 0;
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
#endif // VOXEL_H