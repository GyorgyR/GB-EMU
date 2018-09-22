//
// Created by gyorgy on 19/09/18.
//

#ifndef GB_EMULATOR_HELPER_H
#define GB_EMULATOR_HELPER_H

#include <utility>
#include <cstdint>

#include "ROM.h"

class Helper {
private:
    static ROM loaded_rom;
public:
    static uint16_t ConcatTwoBytes(uint8_t first, uint8_t second);
    static std::pair<uint8_t, uint8_t> DivideIntoTwoBytes(uint16_t value);
    static void LoadRom(ROM rom);

    static ROM *GetLoadedRom();
};


#endif //GB_EMULATOR_HELPER_H
