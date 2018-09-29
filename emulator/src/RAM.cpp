//
// Created by gyorgy on 29/09/18.
//

//#define DEBUG

#include <cstdio>
#include <cstdlib>

#include "../include/RAM.h"

ROM *RAM::loaded_rom = nullptr;
uint8_t RAM::vram[8192];

RAM::RAM()
{
}

RAM::~RAM()
{
}

uint8_t RAM::ReadByteAt(uint16_t address)
{
    uint8_t ret_val = -1;
#ifdef DEBUG
    printf("Read at: 0x%04X", address);
#endif
    switch (address) {
        case 0x0 ... 0x3FFF: {
#ifdef DEBUG
            puts(" (ROM Bank 0)");
#endif
            ret_val = loaded_rom->GetByteAt(address);
            break;
        }
        case 0x4000 ... 0x7FFF: {
#ifdef DEBUG
            puts("(ROM Bank n)");
#endif
            goto UNIMPLEMENTED;
            break;
        }
        case 0x8000 ... 0x9FFF: {
#ifdef DEBUG
            puts(" (VRAM)");
#endif
            int internal_address = address - 0x8000;
#ifdef DEBUG
            printf("address: %d", internal_address);
#endif
            goto UNIMPLEMENTED;
            break;
        }
        UNIMPLEMENTED:
        default:
            printf(" (Unimplemented range: 0x%04X)\n", address);
            exit(1);
    }
    return ret_val;
}

bool RAM::WriteByteAt(uint16_t address, uint8_t value)
{
#ifdef DEBUG
    printf("Write at: 0x%04X, value: 0x%02X", address, value);
#endif
    bool success = false;
    switch (address) {
        case 0x8000 ... 0x9FFF: {
            int internal_address = address - 0x8000;
#ifdef DEBUG
            printf(" (VRAM @%d)\n", internal_address);
#endif
            vram[internal_address] = value;
            success = true;
            break;
        }
        UNIMPLEMENTED:
        default:
            printf(" (Unimplemented range: 0x%04X)\n", address);
            exit(1);
    }
    return success;
}

void RAM::InitRam(ROM *rom)
{
    loaded_rom = rom;
}
