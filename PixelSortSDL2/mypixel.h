#include <random>

class MyPixel {
    public:
        MyPixel();

        // TODO: Make private again
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a = 255;

        float Hue();

    private:
        // Random number generation stuff
        static std::mt19937 rng;
        static std::uniform_int_distribution<std::mt19937::result_type> rand360;
        static bool seeded;
        
        static void RandomHue(unsigned char* out_r, unsigned char* out_g, unsigned char* out_b);
};