//
// Created by gyorgy on 17/09/18.
//

#ifndef GB_EMULATOR_ROM_H
#define GB_EMULATOR_ROM_H
#include <cstdint>
#include "Types.h"

class ROM {
private:
    uint8 *rom;
public:
    ROM(const char *rom_file_path);
    ~ROM();
    int rom_file_size;
    uint8 GetByteAt(uint16 address);
};


#endif //GB_EMULATOR_ROM_H
