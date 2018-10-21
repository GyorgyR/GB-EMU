//
// Created by gyorgy on 29/09/18.
//

#ifndef GB_EMULATOR_RAM_H
#define GB_EMULATOR_RAM_H

#include <cstdio>

#include "ROM.h"
#include "Types.h"

class RAM
{
private:
    static ROM *loadedRom;
    static ROM *bootRom;
    static ROM **activeBootPage;
    static uint8 vram[];
    static uint8 stack[];
    static uint8 workRam[8][4096];

    RAM();
    ~RAM();

public:
    static void InitRam(ROM *rom);

    static void InitBootRom(ROM *boot);
    static uint8_t ReadByteAt(uint16_t address);
    static bool WriteByteAt(uint16_t address, uint8_t value);

    static void DumpVRAM();
};


#endif //GB_EMULATOR_RAM_H
