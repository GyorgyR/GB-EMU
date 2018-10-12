//
// Created by gyorgy on 12/10/18.
//

#define WINDOWHEIGHT 160
#define WINDOWWIDTH 140

#include <iostream>
#include <SDL2/SDL.h>

#include "../include/Window.h"
#include "../include/Configuration.h"
#include "../include/RGBA.h"

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
            WINDOWWIDTH * Configuration::PixelScaleFactor,
            WINDOWHEIGHT * Configuration::PixelScaleFactor,
            SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow ERROR " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, 0, 0);

    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRendere ERROR" << SDL_GetError() << std::endl;
        exit(1);
    }
}

Window::~Window()
{
    SDL_DestroyWindow(window);
    SDL_VideoQuit();
}

void Window::DrawPixel(uint8_t x, uint8_t y, RGBA colour)
{
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderDrawPoint(renderer, x, y);
}
