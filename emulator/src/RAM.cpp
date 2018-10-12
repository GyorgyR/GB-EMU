//
// Created by gyorgy on 29/09/18.
//

#define DEBUG

#include <cstdlib>

#include "../include/RAM.h"
#include "../include/SoundGenerator.h"
#include "../include/VideoRegisters.h"
#include "../include/Helper.h"

ROM *RAM::loadedRom = nullptr;
ROM *RAM::bootRom = nullptr;
ROM **RAM::activeBootPage = &bootRom;
uint8_t RAM::vram[8192];
uint8_t RAM::stack[0x7F];

RAM::RAM()
{
}

RAM::~RAM()
{
}

uint8_t RAM::ReadByteAt(uint16_t address)
{
    uint8_t retVal = -1;
    Helper::RAMLog("[READ ] [@0x%04X]", address);
    switch (address) {
        case 0x0 ... 0x00FF: {
            retVal = (*activeBootPage)->GetByteAt(address);
            Helper::RAMLog(" [ROM PAGE 1]");
            break;
        }
        case 0x0100 ... 0x3FFF: {
            retVal = loadedRom->GetByteAt(address);
            Helper::RAMLog(" [ROM BANK 0]");
            break;
        }
        case 0x4000 ... 0x7FFF: {
            Helper::RAMLog("[ROM BANK N]");
            goto UNIMPLEMENTED;
            break;
        }
        case 0x8000 ... 0x9FFF: {
            int internalAddress = address - 0x8000;
            Helper::RAMLog(" [VRAM@%d]", internalAddress);
            goto UNIMPLEMENTED;
            break;
        }
        case 0xFF80 ... 0xFFFE: {
            int internalAddr = address - 0xFF80;
            Helper::RAMLog(" [STACK@%d]", internalAddr);
            retVal = stack[internalAddr];
            break;
        }
        UNIMPLEMENTED:
        default:printf(" (Unimplemented read range: 0x%04X)\n", address);
            exit(1);
    }
    Helper::RAMLog(" [VALUE 0x%02X]\n", retVal);
    return retVal;
}

bool RAM::WriteByteAt(uint16_t address, uint8_t value)
{
    Helper::RAMLog("[WRITE] [@0x%04X]", address);
    bool success = false;
    switch (address) {
        case 0x8000 ... 0x9FFF: {
            int internalAddress = address - 0x8000;
            Helper::RAMLog(" [VRAM @%d]", internalAddress);
            vram[internalAddress] = value;
            success = true;
            break;
        }
        case 0xFF11: {
            Helper::RAMLog(" [Channel1 Wave Pattern]");
            success = SoundGenerator::ChannelWavePattern(value);
            break;
        }
        case 0xFF12: {
            Helper::RAMLog(" [Channel1 Volume Envelope]");
            success = SoundGenerator::Channel1VolumeEnvelope(value);
            break;
        }
        case 0xFF25: {
            Helper::RAMLog(" [Sound Out Terminal]");
            success = SoundGenerator::SoundOutTerminal(value);
            break;
        }
        case 0xFF26: {
            Helper::RAMLog(" [Sound on/off]");
            success = SoundGenerator::SoundOnOff(value);
            break;
        }
        case 0xFF40: {
            Helper::RAMLog(" [LCDControl]");
            success = VideoRegisters::LCDControl(value);
            break;
        }
        case 0xFF42: {
            Helper::RAMLog(" [ScrollPosY]");
            success = VideoRegisters::ScollPosY(value);
            break;
        }
        case 0xFF47: {
            Helper::RAMLog(" [Video BG Palette]");
            success = VideoRegisters::BGPaletteData(value);
            break;
        }
        case 0xFF50: {
            Helper::RAMLog("[BOOT ROM OFF]");
            activeBootPage = &loadedRom;
            success = true;
            puts("Successfully reached end of boot rom");
            exit(0);
            break;
        }
        case 0xFF80 ... 0xFFFE: {
            int internalAddr = address - 0xFF80;
            Helper::RAMLog(" [STACK@%d]", internalAddr);
            stack[internalAddr] = value;
            success = true;
            break;
        }
        UNIMPLEMENTED:
        default:printf(" (Unimplemented write range: 0x%04X)\n", address);
            exit(1);
    }
    Helper::RAMLog(" [VALUE 0x%02X]\n", value);
    return success;
}

void RAM::InitRam(ROM *rom)
{
    loadedRom = rom;
}

void RAM::InitBootRom(ROM *boot)
{
    bootRom = boot;
}
