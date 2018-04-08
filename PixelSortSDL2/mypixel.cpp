#include "mypixel.h"
#include <cmath>

MyPixel::MyPixel(Uint8 rToSet, Uint8 gToSet, Uint8 bToSet) {
    r = rToSet;
    g = gToSet;
    b = bToSet;
}

float MyPixel::Hue() {
    float _r = float(r);
    float _g = float(g);
    float _b = float(b);

    float max_rgb = fmax(fmax(_r,_g),_b);
    float delta = max_rgb - fmin(fmin(_r,_g),_b);
    if (delta < 0.00001) { return 0; }

    float out;
    if (_r >= max_rgb) {
        out = (_g - _b) / delta;
    } else {
        if (_g >= max_rgb) {
            out = 2.0 + (_b - _r) / delta;
        } else {
            out = 4.0 + (_r - _g) / delta;
        }
    }

    out *= 60.0;
    if (out < 0.0) { out += 360.0; }

    return out;
}