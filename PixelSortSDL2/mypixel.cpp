#include "mypixel.h"
#include <cmath>

// Seed random number generator
std::uniform_int_distribution<std::mt19937::result_type> MyPixel::rand360(0.0,360.0);
bool MyPixel::seeded = false;
std::mt19937 MyPixel::rng;

MyPixel::MyPixel() {
    MyPixel::RandomHue(&r, &g, &b);
}

void MyPixel::RandomHue(unsigned char* out_r, unsigned char* out_g, unsigned char* out_b) {
    if (!seeded) {
        rng.seed(std::random_device()());
        seeded = true;
    }

    // Generate random hue. Saturation and value are at full.
    float hue = MyPixel::rand360(rng);
    if (hue >= 360.0) { hue = 0.0; }
    float sat = 1.0;
    float val = 1.0;

    // Simplified hsv->rgb converter, since we only care about
    // hue in this program.
    double ff;
    long i;

    hue /= 60.0;
    i = (long)hue;
    ff = hue - i;
    float _r, _g, _b;

    switch(i) {
    case 0:
        _r = val;
        _g = -ff;
        _b = 0.0;
        break;
    case 1:
        _r = 1.0 - ff;
        _g = val;
        _b = 0.0;
        break;
    case 2:
        _r = 0.0;
        _g = val;
        _b = -ff;
        break;
    case 3:
        _r = 0.0;
        _g = 1.0 - ff;
        _b = val;
        break;
    case 4:
        _r = -ff;
        _g = 0.0;
        _b = val;
        break;
    case 5:
    default:
        _r = val;
        _g = 0.0;
        _b = 1.0 - ff;
        break;
    }

    *out_r = (unsigned char)(255 * _r);
    *out_g = (unsigned char)(255 * _g);
    *out_b = (unsigned char)(255 * _b);
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