#include "application.h"
#include "mypixel.h"
#include <iostream>

Application::Application() {
    std::cout << "Seeding random number generator and initializing video" << std::endl;
    std::uniform_int_distribution<std::mt19937::result_type> rand256(0,255);
    rng.seed(std::random_device()());

    // Define size of pixel array
    pixels = new MyPixel*[dimension];
    for (int p = 0; p < dimension; p++) {
        pixels[p] = new MyPixel[dimension];
    }
}

Application::~Application() {
    for (int p = 0; p < dimension; p++) {
        delete pixels[p];
    }
    delete pixels;
}

void Application::DrawRandomColorAt(int x, int y) {
    MyPixel pixel(Uint8(rand256(rng)), Uint8(rand256(rng)), Uint8(rand256(rng)));

    SDL_SetRenderDrawColor(renderer, pixel.r, pixel.g, pixel.b, pixel.a);
    SDL_RenderDrawPoint(renderer, x, y);
    pixels[y][x] = pixel;

    Refresh();
}

void Application::Run() {
    SDL_Init(SDL_INIT_VIDEO);

    if (SDL_WasInit(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL2 Video was initialised" << std::endl;
    }

    window = SDL_CreateWindow("PixelSort", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dimension, dimension, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, SDL_RENDERER_ACCELERATED, -1);

    // Initialize the array and display with random colours
    for (int y = 0; y < dimension; y++) {
        for (int x = 0; x < dimension; x++) {
            DrawRandomColorAt(x, y);
        }
    }

    // Perform the sort, which draws the results as it progresses.
    Quicksort(0, dimension*dimension-1);

    // Leave the result on the screen for 10 seconds, then cleanup and quit.
    SDL_Delay(10000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Application::Quicksort (int lo, int hi) {
    if (lo < hi) {
        int p = Partition(lo, hi);
        Quicksort(lo, p - 1);
        Quicksort(p + 1, hi);
    }
}

int Application::Partition (int lo, int hi) {
    //std::cout << "partitioning from " << lo << " to " << hi << std::endl;
    //std::cout << "pivot is at x:" << hi%dimension << " y:" << hi/dimension << std::endl;
    MyPixel pivot = pixels[hi/dimension][hi%dimension];

    int i = lo - 1;

    for (int j = lo; j < hi; j++) {
        if (pixels[j/dimension][j%dimension].Hue() < pivot.Hue()) {
            i++;
            SwapAndDrawPixels(i, j);
        }
    }
    SwapAndDrawPixels(hi, i+1);

    return i + 1;
}

void Application::SwapAndDrawPixels(int a, int b) {
    int ax = a%dimension;
    int ay = a/dimension;
    int bx = b%dimension;
    int by = b/dimension;

    // Swap pixels. Coordinate swapping needs fixing badly.
    MyPixel temp = pixels[ay][ax];
    pixels[ay][ax] = pixels[by][bx];
    pixels[by][bx] = temp;

    // Draw first pixel
    SDL_SetRenderDrawColor(renderer, pixels[ay][ax].r, pixels[ay][ax].g, pixels[ay][ax].b, pixels[ay][ax].a);
    SDL_RenderDrawPoint(renderer, ax, ay);

    // Draw second pixel
    SDL_SetRenderDrawColor(renderer, pixels[by][bx].r, pixels[by][bx].g, pixels[by][bx].b, pixels[by][bx].a);
    SDL_RenderDrawPoint(renderer, bx, by);

    Refresh();
}

void Application::Refresh() {
    if (frameCount++ % speedUp == 0) {
        SDL_RenderPresent(renderer);
    }
}