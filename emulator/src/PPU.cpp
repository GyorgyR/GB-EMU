//
// Created by gyorgy on 13/10/18.
//

#define CLOCKSPERLINE 20+43+51
#define LINES 153
#define SPRITELENGTH 16

#include "../include/PPU.h"
#include "../include/VideoRegisters.h"
#include "../include/RAM.h"
#include "../include/Types.h"
#include "../include/Helper.h"

unsigned int PPU::currentLine = 0;
unsigned int PPU::currentLineCycle = 0;
unsigned int PPU::currentPixel = 0;
Window *PPU::window = nullptr;

PPU::PPU() {}

PPU::~PPU() {}

void PPU::Update(int cycles)
{
    for (int currentCycle = 0; currentCycle < cycles; ++currentCycle) {
        if (++currentLineCycle > CLOCKSPERLINE) {
            ++currentLine;
            currentLineCycle = 0;
        }

        if (currentLine > LINES) currentLine = 0;
        VideoRegisters::LCDYCoordinate(currentLine);

        if (currentLine <= window->height) {
            if (currentPixel > window->width) currentPixel = 0;
            int currentMapLine = (currentLine + VideoRegisters::ScrollPosY()) / 8;
            int currentMapLineCycle = currentPixel / 8;
            uint16 tileAddress =
                    VideoRegisters::BGTileMapBaseAddr() + (currentMapLine * 32) + (currentMapLineCycle * 32);
            uint8 colour = (RAM::ReadByteAt(tileAddress) == 0) ? 255 : 128;
            RGBA drawColour(colour);
            window->DrawPixel(currentPixel++, currentLine, drawColour);
        }
    }
    window->UpdateScreen();
}

void PPU::SetWindow(Window *currWindow)
{
    window = currWindow;
}
