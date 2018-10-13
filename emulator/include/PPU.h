//
// Created by gyorgy on 13/10/18.
//

#ifndef GB_EMULATOR_PPU_H
#define GB_EMULATOR_PPU_H


#include "Window.h"

class PPU
{
private:
    //Make class static
    PPU();

    ~PPU();

    //Variables
    static unsigned int currentLine;
    static unsigned int currentLineCycle;
    static unsigned int currentPixel;
    static Window *window;
public:
    static void SetWindow(Window *currWindow);

    static void Update(int cycles);
};


#endif //GB_EMULATOR_PPU_H
