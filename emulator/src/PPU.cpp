//
// Created by gyorgy on 13/10/18.
//

#define OAMSEARCHCYCLES 80
#define CLOCKSPERLINE OAMSEARCHCYCLES+172+204
#define LINES 153
#define TILEDATALENGTH 16

#include "../include/PPU.h"
#include "../include/VideoRegisters.h"
#include "../include/MMU.h"
#include "../include/Types.h"
#include "../include/Helper.h"
#include "../include/Configuration.h"

unsigned int PPU::currentLine = 0;
unsigned int PPU::currentLineCycle = 0;
unsigned int PPU::currentPixel = 0;
unsigned int PPU::fifoFetchState = 0;
unsigned int PPU::PPUState = 0;
int PPU::lastTileNo = 0;
uint8 PPU::lastByte1 = 0;
int PPU::decodedBytes[8];
std::queue<int> PPU::fifo;
Window *PPU::window = nullptr;
uint16 PPU::fetcherLastAddr = 0;
int PPU::discardedPixels = 0;

PPU::PPU() {}

PPU::~PPU() {}

void PPU::Update(int cycles)
{
    for (int iteration = 0; iteration < cycles; ++iteration) {

        if (++currentLineCycle > CLOCKSPERLINE) {
            ++currentLine;
            currentLineCycle = 0;
            discardedPixels = 0;
            PPUState = 0;
            VideoRegisters::LCDStatMode(2);

            if (currentLine == window->height) {
                window->UpdateScreen();
                PPUState = 3;
                VideoRegisters::LCDStatMode(1);
            } else if (currentLine > LINES) {
                currentLine = 0;
                PPUState = 0;
                VideoRegisters::LCDStatMode(2);
            }
            VideoRegisters::LCDYCoordinate(currentLine);

            fetcherLastAddr =
                    VideoRegisters::BGTileMapBaseAddr() +
                    ((currentLine + VideoRegisters::ScrollPosY()) / 8) * 32
                    ;
        }

        switch (PPUState) {
            case 0: { //OAMSEARCH
                if (currentLineCycle == OAMSEARCHCYCLES) {
                    PPUState = 1;
                    VideoRegisters::LCDStatMode(3);
                }
                break;
            }
            case 1: { //Pixel Draw
                //Check for a window
                if (VideoRegisters::IsWindowEnabled) {
                    if (
                            currentLine >= VideoRegisters::WindowPosY() &&
                            currentPixel >= VideoRegisters::WindowPosX() - 7
                            ) {
                        //fifo = std::queue<int>();
                        Helper::Log("Turn on window");
                        exit(1);
                    }
                }
                if (currentLineCycle % 2 == 1) FifoFetch();
                if (fifo.size() > 8) FifoPush();
                if (currentPixel == window->width) {
                    PPUState = 2;
                    VideoRegisters::LCDStatMode(0);
                    currentPixel = 0;
                    fifo = std::queue<int>();
                    fifoFetchState = 0;
                }
                break;
            }
            case 2: { //H-BLANK
                break;
            }
            case 3: { //V-BLANK
                break;
            }
            default: { //ERROR
                Helper::Log("PPU ERROR -- INVALID STATE");
                exit(1);
            }
        }
    }
}


void PPU::FifoFetch()
{
    Helper::PPULog("FETCH\n");
    switch (fifoFetchState) {
        case 0: { //tile map fetch
            lastTileNo = MMU::ReadByteAt(fetcherLastAddr++);
            Helper::PPULog("  Fetched tile map: %d\n", lastTileNo);
            ++fifoFetchState;
            return;
        }
        case 1: { //byte 1 fetch
            uint8 byte1 = MMU::ReadByteAt(currentTileRowBaseAddr());
            Helper::PPULog("  Fetched byte1: 0x%02X\n", byte1);
            lastByte1 = byte1;
            ++fifoFetchState;
            return;
        }
        case 2: { //byte 2 fetch, decode and store to fifo
            uint8 byte2 = MMU::ReadByteAt(currentTileRowBaseAddr() + 1);
            Helper::PPULog("  Fetched byte2: 0x%02X\n", byte2);

            for (int i = 0; i < 8; ++i) {
                decodedBytes[i] = Helper::IsBitSet(byte2, i) ? 2 : 0;
                decodedBytes[i] += Helper::IsBitSet(lastByte1, i) ? 1 : 0;
            }

            if (fifo.size() <= 8) {
                for (int i = 7; i >= 0; --i) {
                    fifo.push(decodedBytes[i]);
                }
                fifoFetchState = 0;
            }
            else
                fifoFetchState = 3;
            return;
        }
        case 3: { // idle (put into fifo if possible)
            Helper::PPULog("  IDLE\n");
            if (fifo.size() <= 8) {
                for (int i = 7; i >= 0; --i) {
                    fifo.push(decodedBytes[i]);
                }
                fifoFetchState = 0;
            }
            else
                fifoFetchState = 3;
            return;
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
    baseAddr += ((currentLine + VideoRegisters::ScrollPosY()) % 8) * 2;
    return baseAddr;
}

void PPU::FifoPush()
{
    Helper::PPULog("PUSH (%d)\n", fifo.size());

    int colour = fifo.front();
    fifo.pop();

    if (discardedPixels < VideoRegisters::ScrollPosX()) ++discardedPixels;
    else window->DrawPixel(currentPixel++, currentLine, VideoRegisters::GetBGColour(colour));
}

void PPU::SetWindow(Window *currWindow)
{
    window = currWindow;
}

