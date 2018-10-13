//
// Created by gyorgy on 13/10/18.
//

#include <chrono>
#include <thread>

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

    for (unsigned int i = 0; i < (window.width + window.height) / 2; i += window.height / window.width)
        window.DrawPixel(i, i, blue);
    window.UpdateScreen();

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}