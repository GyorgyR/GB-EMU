//
// Created by gyorgy on 17/09/18.
//

#ifndef GB_EMULATOR_ROM_H
#define GB_EMULATOR_ROM_H
#include <cstdint>

class ROM {
private:
    uint8_t *rom;
public:
    ROM(const char *rom_file_path);
    ~ROM();
    int rom_file_size;
    uint8_t GetByteAt(uint16_t address);
};


#endif //GB_EMULATOR_ROM_H
