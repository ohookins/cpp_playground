#include <SDL2/SDL.h>
#include <random>

class MyPixel;

class Application {
    public:
        Application();
        ~Application();

        void Run();

    private:
        // Random number generation stuff
        std::mt19937 rng;
        std::uniform_int_distribution<std::mt19937::result_type> rand256;

        const int dimension = 500;
        int speedUp = 50;
        uint frameCount = 0;

        // SDL stuff
        MyPixel** pixels;
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        // Methods
        void DrawRandomColorAt(int x, int y);
        void SwapAndDrawPixels(int a, int b);
        void Refresh();
        void Quicksort(int lo, int hi);
        int Partition(int lo, int hi);
};