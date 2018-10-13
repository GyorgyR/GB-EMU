//
// Created by gyorgy on 12/10/18.
//

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
            //width,
            //height,
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
    unsigned int tX = x * Configuration::PixelScaleFactor;
    unsigned int tY = y * Configuration::PixelScaleFactor;

    for (unsigned int xPos = 0; xPos < Configuration::PixelScaleFactor; xPos++) {
        for (unsigned int yPos = 0; yPos < Configuration::PixelScaleFactor; ++yPos) {
            SDL_RenderDrawPoint(renderer, tX + xPos, tY + yPos);
        }
    }
}

void Window::UpdateScreen()
{
    SDL_RenderPresent(renderer);
}
