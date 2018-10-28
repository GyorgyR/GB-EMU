//
// Created by gyorgy on 12/10/18.
//

#define FPS_COUNTER

#include <SDL2/SDL.h>
#include <chrono>
#include <thread>
#include <iostream>

#include "../include/Window.h"
#include "../include/Configuration.h"
#include "../include/RGBA.h"
#include "../include/MMU.h"
#include "../include/Types.h"

uint32 frameCount = 0;
uint64 startTime;

Window::Window()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init ERROR: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(
            Configuration::WindowTitle.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width * Configuration::PixelScaleFactor,
            height * Configuration::PixelScaleFactor,
            SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow ERROR " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED /* | SDL_RENDERER_PRESENTVSYNC */);

    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer ERROR" << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_RenderSetScale(renderer, Configuration::PixelScaleFactor, Configuration::PixelScaleFactor);

    std::cout << "\n";
    startTime = SDL_GetPerformanceCounter();
}

Window::~Window()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    SDL_DestroyWindow(window);
    SDL_VideoQuit();
}

void Window::DrawPixel(uint8_t x, uint8_t y, RGBA colour)
{
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderDrawPoint(renderer, x, y);
}

void Window::UpdateScreen()
{
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            exit(0);
    }

    SDL_RenderPresent(renderer);
    #ifdef FPS_COUNTER
    uint64 timeNow = SDL_GetPerformanceCounter();
    uint64 freq = SDL_GetPerformanceFrequency();
    int seconds = (timeNow - startTime) / static_cast<double>(freq);

    ++frameCount;

    if (seconds == 1) {
        std::cout << "\e[A";
        std::cout << "\r" << frameCount << "\n";
        std::flush(std::cout);
        frameCount = 0;
        startTime = timeNow;
    }
    #endif
}
