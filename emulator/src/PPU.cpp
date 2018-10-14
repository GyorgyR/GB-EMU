//
// Created by gyorgy on 13/10/18.
//

#define OAMSEARCHCYCLES 80
#define CLOCKSPERLINE OAMSEARCHCYCLES+172+204
#define LINES 153
#define TILEDATALENGTH 16

#include "../include/PPU.h"
#include "../include/VideoRegisters.h"
#include "../include/RAM.h"
#include "../include/Types.h"
#include "../include/Helper.h"
#include "../include/Configuration.h"

unsigned int PPU::currentLine = 0;
unsigned int PPU::currentLineCycle = 0;
unsigned int PPU::currentPixel = 0;
unsigned int PPU::fifoFetchState = 0;
unsigned int PPU::lastTileNo = 0;
int PPU::decodedBytes[8];
std::queue<int> PPU::fifo;
Window *PPU::window = nullptr;

PPU::PPU() {}

PPU::~PPU() {}

void PPU::Update(int cycles)
{
    for (int currentCycle = 0; currentCycle < cycles; ++currentCycle) {
        if (++currentLineCycle > CLOCKSPERLINE) {
            ++currentLine;
            currentLineCycle = 0;
            currentPixel = 0;
        }

        if (currentLine > LINES) currentLine = 0;
        VideoRegisters::LCDYCoordinate(currentLine);

        if (currentLine == window->height + 1) window->UpdateScreen();

        bool isInRenderMode =
                currentLine < window->height &&
                currentLineCycle > OAMSEARCHCYCLES &&
                currentPixel < window->width;

        if (isInRenderMode) {

            if (currentLineCycle % 2 == 1) FifoFetch();
            FifoPush();

            /*int currentMapLine = (currentLine + VideoRegisters::ScrollPosY()) / 8;
            int currentMapLineCycle = currentPixel / 8;
            uint16 tileAddress =
                    VideoRegisters::BGTileMapBaseAddr() + (currentMapLine * 32) + (currentMapLineCycle * 32);
            uint8 colour = (RAM::ReadByteAt(tileAddress) == 0) ? 255 : 128;
            RGBA drawColour(colour);
            window->DrawPixel(currentPixel++, currentLine, drawColour);*/
        }
    }
}

void PPU::FifoFetch()
{
    switch (fifoFetchState) {
        case 0: { //tile map fetch
            int tileMapLine = (currentLine + VideoRegisters::ScrollPosY()) / 8;
            int tileMapCol = (currentPixel + VideoRegisters::ScrollPosX()) / 8;

            uint16 tileMapAddress =
                    VideoRegisters::BGTileMapBaseAddr() +
                    (tileMapLine * 32) +
                    (tileMapCol * 32);

            lastTileNo = RAM::ReadByteAt(tileMapAddress);
            ++fifoFetchState;
            break;
        }
        case 1: { //byte 1 fetch and decode
            uint8 byte1 = RAM::ReadByteAt(currentTileRowBaseAddr());
            uint8 bitmask = 0b11;
            for (int i = 0; i < 4; ++i) {
                decodedBytes[4 + i] = byte1 & bitmask;
                byte1 >>= 1;
            }
            ++fifoFetchState;
            break;
        }
        case 2: { //byte 2 fetch, decode and store to fifo
            uint8 byte2 = RAM::ReadByteAt(currentTileRowBaseAddr() + 1);
            uint8 bitmask = 0b11;
            for (int i = 0; i < 4; ++i) {
                decodedBytes[i] = byte2 & bitmask;
                byte2 >>= 1;
            }
            if (fifo.size() <= 8) {
                for (int i = 7; i > 0; --i) {
                    fifo.push(decodedBytes[i]);
                }
                fifoFetchState = 0;
            }
            else
                fifoFetchState = 3;

            break;
        }
        case 3: { // idle (put into fifo if possible)
            if (fifo.size() <= 8) {
                for (int i = 7; i > 0; --i) {
                    fifo.push(decodedBytes[i]);
                }
                fifoFetchState = 0;
            }
            else
                fifoFetchState = 3;
            break;
        }
        default: //ERROR
            Helper::Log("FIFO FETCH ERROR -- INVALID STATE");
            exit(1);
    }

}

uint16 PPU::currentTileRowBaseAddr()
{
    //Get base address of tile data
    uint16 baseAddr = VideoRegisters::BGTileDataBaseAddr();
    //Add the number of the tile times length of tiles in bytes, get base of tile
    baseAddr += lastTileNo * TILEDATALENGTH;
    //Add the current row (in the tile) times 2 to the tile base to get row base
    baseAddr += (currentLine % 8) * 2;
    return baseAddr;
}

void PPU::FifoPush()
{
    if (fifo.size() <= 8) return;

    int colour = fifo.front();
    fifo.pop();
    window->DrawPixel(currentPixel++, currentLine, Configuration::Colours[colour]);
}

void PPU::SetWindow(Window *currWindow)
{
    window = currWindow;
}
