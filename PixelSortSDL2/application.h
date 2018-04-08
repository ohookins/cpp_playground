#include <SDL2/SDL.h>

class MyPixel;

class Application {
    public:
        Application();
        ~Application();

        void Run();

    private:
        const int dimension = 500;
        int speedUp = 100;
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