#include <SDL2/SDL.h>
#include <random>

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
        SDL_Color* pixels = nullptr;
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        void DrawRandomColorAt(int x, int y);
};