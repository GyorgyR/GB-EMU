//
// Created by gyorgy on 13/10/18.
//

#ifndef GB_EMULATOR_PPU_H
#define GB_EMULATOR_PPU_H

#include <queue>

#include "Window.h"
#include "Types.h"

enum TileTypes {BG, OBJ, WINDOW};

struct FifoElement {
    uint8 colour;
    TileTypes source;
};

class PPU
{
private:
    //Constructor and destructor
    //Make class static
    PPU();
    ~PPU();

    //Variables
    static unsigned int currentLine;
    static unsigned int currentLineCycle;
    static unsigned int currentPixel;
    static unsigned int fifoFetchState;
    static unsigned int PPUState;
    static int lastTileNo;
    static uint8 lastByte1;
    static int decodedBytes[];
    static std::queue<FifoElement> fifo;
    static Window *window;
    static int discardedPixels;
    static uint16 fetcherLastAddr;

    //functions
    static void FifoFetch();
    static void FifoPush();
    static inline uint16 currentTileRowBaseAddr();
    static inline void PopulateFifo();

public:
    static void SetWindow(Window *currWindow);
    static void Update(int cycles);
};


#endif //GB_EMULATOR_PPU_H
