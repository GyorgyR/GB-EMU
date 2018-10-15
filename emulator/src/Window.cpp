//
// Created by gyorgy on 12/10/18.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <chrono>
#include <thread>

#include "../include/Window.h"
#include "../include/Configuration.h"
#include "../include/RGBA.h"
#include "../include/RAM.h"

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

    renderer = SDL_CreateRenderer(window, 0, 0);

    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer ERROR" << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_RenderSetScale(renderer, Configuration::PixelScaleFactor, Configuration::PixelScaleFactor);
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
    SDL_RenderPresent(renderer);
}
