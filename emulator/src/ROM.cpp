//
// Created by gyorgy on 17/09/18.
//

#include <fstream>
#include "../include/ROM.h"

ROM::ROM(const char *rom_file_path)
{
    std::ifstream rom_file(rom_file_path, std::ios::in | std::ios::binary);

    if (rom_file) {
        rom_file.unsetf(std::ios::skipws);

        rom_file.seekg(0, std::ios::end);
        rom_file_size = rom_file.tellg();
        rom_file.seekg(0, std::ios::beg);

        rom = new uint8[rom_file_size];

        rom_file.read(reinterpret_cast<char *>(rom), rom_file_size);

        rom_file.close();
    }
}

ROM::~ROM()
{

}

uint8 ROM::GetByteAt(uint16 address)
{
    return rom[address];
}
