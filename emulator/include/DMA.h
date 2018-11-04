//
// Created by gyorgy on 30/10/18.
//

#ifndef GB_EMULATOR_DMA_H
#define GB_EMULATOR_DMA_H


#include "Types.h"

class DMA
{
private:
    //Make class static
    DMA();
    ~DMA();

    //Variables
    static const uint destStartAddr = 0xFE00;
    static const uint destinEndAddr = 0xFE9F;

    static uint16 startAddress;
    static uint16 currentDestAddress;

public:
    static void Update(int cycles);
    static bool Start(uint8 address);
};


#endif //GB_EMULATOR_DMA_H
