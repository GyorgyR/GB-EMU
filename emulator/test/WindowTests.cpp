//
// Created by gyorgy on 13/10/18.
//

#include <chrono>
#include <thread>
#include <iostream>

#include "../include/Window.h"
#include "../include/RGBA.h"

int main()
{
    Window window;

    RGBA bgColour(255, 255, 255);
    RGBA red(255, 0, 0);
    RGBA green(0, 255, 0);
    RGBA blue(0, 0, 255);

    for (unsigned int i = 0; i < window.width; ++i) {
        for (unsigned int j = 0; j < window.height; ++j) {
            window.DrawPixel(i, j, bgColour);
        }
    }
    window.UpdateScreen();

    for (int i = 0; i < window.height; i += 1) {
        for (int j = 0; j < window.width; j += 2) {
            window.DrawPixel(j + (i % 2), i, blue);
        }
    }

    for (int i = 0; i < 144; i += 1) {
        for (int j = 1; j < 160; j += 2) {
            window.DrawPixel(j - (i % 2), i, red);
        }
    }
    window.UpdateScreen();

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}