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
int PPU::lastTileNo = 0;
uint8 PPU::lastByte1 = 0;
int PPU::decodedBytes[8];
std::queue<int> PPU::fifo;
Window *PPU::window = nullptr;

PPU::PPU() {}

PPU::~PPU() {}

void PPU::Update(int cycles)
{
    for (int iteration = 0; iteration < cycles; ++iteration) {
        if (++currentLineCycle > CLOCKSPERLINE) {
            ++currentLine;
            currentLineCycle = 0;
            currentPixel = 0;
            fifo = std::queue<int>();
            fifoFetchState = 0;
            //Helper::PPULog("\n");
        }

        if (currentLine > LINES) currentLine = 0;
        VideoRegisters::LCDYCoordinate(currentLine);

        if (currentLine == window->height) {
            window->UpdateScreen();
            continue;
        }
        else if (currentLine > window->height) continue;

        bool isInRenderMode =
                currentLine < window->height &&
                currentLineCycle > OAMSEARCHCYCLES &&
                currentPixel < window->width;

        if (isInRenderMode) {

            if (currentLineCycle % 2 == 1) FifoFetch();
            if (fifo.size() > 8) FifoPush();

            /*
            int currentMapLine = (currentLine + VideoRegisters::ScrollPosY()) / 8;
            int currentMapLineCycle = (currentPixel + VideoRegisters::ScrollPosX()) / 8;

            uint16 tileAddress =
                    VideoRegisters::BGTileMapBaseAddr() +
                    (currentMapLine * 32) +
                    (currentMapLineCycle)
                    ;

            lastTileNo = RAM::ReadByteAt(tileAddress);

            uint16 address = currentTileRowBaseAddr();
            uint8 byte1 = RAM::ReadByteAt(address);
            uint8 byte2 = RAM::ReadByteAt(address + 1);

            int posInTile = currentPixel % 8;
            int colour = Helper::IsBitSet(byte2, 7 - posInTile) ? 2 : 0;
            colour += Helper::IsBitSet(byte1, 7 - posInTile) ? 1 : 0;

            window->DrawPixel(currentPixel++, currentLine, Configuration::Colours[colour]);
             */
        }
    }
}


void PPU::FifoFetch()
{
    Helper::PPULog("FETCH\n");
    switch (fifoFetchState) {
        case 0: { //tile map fetch
            int tileMapLine = (currentLine + VideoRegisters::ScrollPosY()) / 8;
            int tileMapCol = (currentPixel + VideoRegisters::ScrollPosX() + 16) / 8;

            uint16 tileMapAddress =
                    VideoRegisters::BGTileMapBaseAddr() +
                    (tileMapLine * 32) +
                    tileMapCol;

            lastTileNo = RAM::ReadByteAt(tileMapAddress);
            Helper::PPULog("  Fetched tile map: %d\n", lastTileNo);
            ++fifoFetchState;
            return;
        }
        case 1: { //byte 1 fetch
            uint8 byte1 = RAM::ReadByteAt(currentTileRowBaseAddr());
            Helper::PPULog("  Fetched byte1: 0x%02X\n", byte1);
            lastByte1 = byte1;
            ++fifoFetchState;
            return;
        }
        case 2: { //byte 2 fetch, decode and store to fifo
            uint8 byte2 = RAM::ReadByteAt(currentTileRowBaseAddr() + 1);
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

    window->DrawPixel(currentPixel++, currentLine, Configuration::Colours[colour]);
}

void PPU::SetWindow(Window *currWindow)
{
    window = currWindow;
}

