#include "application.h"
#include <iostream>

Application::Application() {
    std::cout << "Seeding random number generator and initializing video" << std::endl;
    std::uniform_int_distribution<std::mt19937::result_type> rand256(0,255);
    rng.seed(std::random_device()());

    // Define size of pixel array
    pixels = new SDL_Color[dimension*dimension];
}

SDL_Color Application::DrawRandomColorAt(int x, int y, SDL_Renderer* renderer) {
    SDL_Color color;
    color.r = (Uint8)rand256(rng);
    color.g = (Uint8)rand256(rng);
    color.b = (Uint8)rand256(rng);
    color.a = (Uint8)255;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, x, y);
    return color;
}

void Application::Run() {
    SDL_Init(SDL_INIT_VIDEO);

    if (SDL_WasInit(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL2 Video was initialised" << std::endl;
    }

    SDL_Window* window = SDL_CreateWindow("PixelSort", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dimension, dimension, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, SDL_RENDERER_ACCELERATED, -1);

    for (int y = 0; y < dimension; y++) {
        for (int x = 0; x < dimension; x++) {
            pixels[dimension*y+x] = DrawRandomColorAt(x, y, renderer);
            if (frameCount++ % speedUp == 0) {
                SDL_RenderPresent(renderer);
            }
        }
    }

    SDL_Delay(10000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}