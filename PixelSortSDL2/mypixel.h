#include <SDL2/SDL.h>

class MyPixel {
    public:
        // TODO: Make private again
        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a = 255;

        MyPixel() {};
        MyPixel(Uint8 r, Uint8 g, Uint8 b);

        float Hue();

    private:
};