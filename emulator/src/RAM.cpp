//
// Created by gyorgy on 29/09/18.
//

#include <cstdlib>

#include "../include/RAM.h"
#include "../include/SoundGenerator.h"
#include "../include/VideoRegisters.h"
#include "../include/Helper.h"
#include "../include/Types.h"
#include "../include/RegisterBank.h"

ROM *RAM::loadedRom = nullptr;
ROM *RAM::bootRom = nullptr;
ROM **RAM::activeBootPage = &bootRom;
uint8 RAM::vram[8192];
uint8 RAM::stack[0x7F];
uint8 RAM::workRam[8][4096];

RAM::RAM()
{
}

RAM::~RAM()
{
}

uint8 RAM::ReadByteAt(uint16 address)
{
    uint8 retVal = -1;
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
            retVal = loadedRom->GetByteAt(address);
            Helper::RAMLog("[ROM BANK N]");
            break;
        }
        case 0x8000 ... 0x9FFF: {
            int internalAddress = address - 0x8000;
            Helper::RAMLog(" [VRAM@%d]", internalAddress);
            retVal = vram[internalAddress];
            break;
        }
        case 0xFF42: {
            Helper::RAMLog(" [ScrollPosY]");
            retVal = VideoRegisters::ScrollPosY();
            break;
        }
        case 0xFF44: {
            Helper::RAMLog(" [LCDY]");
            retVal = VideoRegisters::LCDYCoordinate();
            break;
        }
        case 0xFF80 ... 0xFFFE: {
            int internalAddr = address - 0xFF80;
            Helper::RAMLog(" [STACK@%d]", internalAddr);
            retVal = stack[internalAddr];
            break;
        }
        UNIMPLEMENTED:
        default:
            printf(" (Unimplemented read range: 0x%04X)\n", address);
            exit(1);
    }
    Helper::RAMLog(" [VALUE 0x%02X]\n", retVal);
    return retVal;
}

bool RAM::WriteByteAt(uint16 address, uint8 value)
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
        case 0xC000 ... 0xCFFF: {
            int internalAddress = address - 0xC000;
            Helper::RAMLog(" [WRAM0@d]", internalAddress);
            workRam[0][internalAddress] = value;
            success = true;
            break;
        }
        case 0xD000 ... 0xDFFF : {
            int intenalAddress = address - 0xD000;
            Helper::RAMLog(" [WRAM1%d]", intenalAddress);
            workRam[1][intenalAddress] = value;
            success = true;
            break;
        }
        case 0xFF0F: {
            Helper::RAMLog(" [Interrupt Flag]");
            RegisterBank::InterruptFlag(value);
            success = true;
            break;
        }
        case 0xFF11: {
            Helper::RAMLog(" [Channel1 Wave Pattern]");
            success = SoundGenerator::Channel1WavePattern(value);
            break;
        }
        case 0xFF12: {
            Helper::RAMLog(" [Channel1 Volume Envelope]");
            success = SoundGenerator::Channel1VolumeEnvelope(value);
            break;
        }
        case 0xFF13: {
            Helper::RAMLog(" [Channel1 Freq-lo]");
            success = SoundGenerator::Channel1FreqLo(value);
            break;
        }
        case 0xFF14: {
            Helper::RAMLog(" [Channel1 Freq-hi]");
            success = SoundGenerator::Channel1FreqHi(value);
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
            success = VideoRegisters::ScrollPosY(value);
            break;
        }
        case 0xFF43: {
            Helper::RAMLog(" [ScrollPosX]");
            success = VideoRegisters::ScrollPosX(value);
            break;
        }
        case 0xFF47: {
            Helper::RAMLog(" [Video BG Palette]");
            success = VideoRegisters::BGPaletteData(value);
            break;
        }
        case 0xFF50: {
            Helper::RAMLog(" [BOOT ROM OFF]");
            activeBootPage = &loadedRom;
            success = true;
            puts("Successfully reached end of boot rom");
            //exit(0);
            break;
        }
        case 0xFF80 ... 0xFFFE: {
            int internalAddr = address - 0xFF80;
            Helper::RAMLog(" [STACK@%d]", internalAddr);
            stack[internalAddr] = value;
            success = true;
            break;
        }
        case 0xFFFF: {
            Helper::RAMLog(" [Interrupt Enable]");
            RegisterBank::InterruptFlag(value);
            success = true;
            break;
        }
        default:
            printf(" (Unimplemented write range: 0x%04X)\n", address);
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

void RAM::DumpVRAM()
{
    for (int i = 0x8000; i < 0xA000; ++i) {
        Helper::Log("0x%04X: 0x%02X", i, vram[i - 0x8000]);
    }
}


