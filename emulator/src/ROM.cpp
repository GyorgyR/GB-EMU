//
// Created by gyorgy on 17/09/18.
//

#include <fstream>
#include "../include/ROM.h"

uint8_t *ROM::rom;
int ROM::rom_file_size = 0;

ROM::ROM(const char *rom_file_path)
{
    std::ifstream rom_file(rom_file_path, std::ios::in | std::ios::binary);

    if (!rom_file) {
        fprintf(stderr, "Error opening file: %s\n", rom_file_path);
        exit(1);
    }

    rom_file.unsetf(std::ios::skipws);

    rom_file.seekg(0, std::ios::end);
    rom_file_size = rom_file.tellg();
    rom_file.seekg(0, std::ios::beg);

    rom = new uint8_t[rom_file_size];

    rom_file.read(reinterpret_cast<char *>(rom), rom_file_size);

    rom_file.close();
}

ROM::~ROM()
{

}

uint8_t ROM::GetByteAt(uint16_t address)
{
    return rom[address];
}
