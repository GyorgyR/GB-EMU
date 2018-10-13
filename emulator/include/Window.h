//
// Created by gyorgy on 12/10/18.
//

#ifndef GB_EMULATOR_WINDOW_H
#define GB_EMULATOR_WINDOW_H

#include <cstdint>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include "RGBA.h"


class Window
{
public:
    const unsigned int width = 160;
    const unsigned int height = 144;

    Window();
    ~Window();

    void DrawPixel(uint8_t x, uint8_t y, RGBA colour);

    void UpdateScreen();

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
};


#endif //GB_EMULATOR_WINDOW_H
