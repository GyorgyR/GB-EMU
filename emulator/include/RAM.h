//
// Created by gyorgy on 29/09/18.
//

#ifndef GB_EMULATOR_RAM_H
#define GB_EMULATOR_RAM_H


#include "ROM.h"

class RAM
{
private:
    static ROM *loaded_rom;
    static uint8_t vram[];

    RAM();

    ~RAM();

public:
    static void InitRam(ROM *rom);

    static uint8_t ReadByteAt(uint16_t address);

    static bool WriteByteAt(uint16_t address, uint8_t value);
};


#endif //GB_EMULATOR_RAM_H
