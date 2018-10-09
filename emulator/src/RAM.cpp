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
FILE *RAM::debugStream = stdout;

RAM::RAM()
{
}

RAM::~RAM()
{
}

uint8_t RAM::ReadByteAt(uint16_t address)
{
    uint8_t retVal = -1;
    #ifdef DEBUG
    fprintf(debugStream, "[READ ] [@0x%04X]", address);
    fflush(debugStream);
    #endif
    switch (address) {
        case 0x0 ... 0x00FF: {
            retVal = (*activeBootPage)->GetByteAt(address);
            #ifdef DEBUG
            fprintf(debugStream, " [ROM Page 1]");
            #endif
            break;
        }
        case 0x0100 ... 0x3FFF: {
            retVal = loadedRom->GetByteAt(address);
            #ifdef DEBUG
            fprintf(debugStream, " [ROM Bank 0]");
            #endif
            break;
        }
        case 0x4000 ... 0x7FFF: {
            #ifdef DEBUG
            fprintf(debugStream, "[ROM Bank n]");
            #endif
            goto UNIMPLEMENTED;
            break;
        }
        case 0x8000 ... 0x9FFF: {
            int internalAddress = address - 0x8000;
            #ifdef DEBUG
            fprintf(debugStream, " [VRAM@%d]", internalAddress);
            #endif
            goto UNIMPLEMENTED;
            break;
        }
        case 0xFF80 ... 0xFFFE: {
            int internalAddr = address - 0xFF80;
            #ifdef DEBUG
            fprintf(debugStream, " [Stack@%d]", internalAddr);
            #endif
            retVal = stack[internalAddr];
            break;
        }
        UNIMPLEMENTED:
        default:printf(" (Unimplemented read range: 0x%04X)\n", address);
            exit(1);
    }
    #ifdef DEBUG
    fprintf(debugStream, " [VALUE 0x%02X]\n", retVal);
    fflush(debugStream);
    #endif
    return retVal;
}

bool RAM::WriteByteAt(uint16_t address, uint8_t value)
{
    #ifdef DEBUG
    fprintf(debugStream, "[WRITE] [@0x%04X]", address);
    #endif
    bool success = false;
    switch (address) {
        case 0x8000 ... 0x9FFF: {
            int internalAddress = address - 0x8000;
            #ifdef DEBUG
            fprintf(debugStream, " [VRAM @%d]", internalAddress);
            #endif
            vram[internalAddress] = value;
            success = true;
            break;
        }
        case 0xFF11: {
            #ifdef DEBUG
            fprintf(debugStream, " [Channel1 Wave Pattern]");
            #endif
            success = SoundGenerator::ChannelWavePattern(value);
            break;
        }
        case 0xFF12: {
            #ifdef DEBUG
            fprintf(debugStream, " [Channel1 Volume Envelope]");
            #endif
            success = SoundGenerator::Channel1VolumeEnvelope(value);
            break;
        }
        case 0xFF25: {
            #ifdef DEBUG
            fprintf(debugStream, " [Sound Out Terminal]");
            #endif
            success = SoundGenerator::SoundOutTerminal(value);
            break;
        }
        case 0xFF26: {
            #ifdef DEBUG
            fprintf(debugStream, " [Sound on/off]");
            #endif
            success = SoundGenerator::SoundOnOff(value);
            break;
        }
        case 0xFF40: {
            #ifdef DEBUG
            fprintf(debugStream, " [LCDControl]");
            #endif
            success = VideoRegisters::LCDControl(value);
            break;
        }
        case 0xFF42: {
            #ifdef DEBUG
            fprintf(debugStream, " [ScrollPosY]");
            #endif
            success = VideoRegisters::ScollPosY(value);
            break;
        }
        case 0xFF47: {
            #ifdef DEBUG
            fprintf(debugStream, " [Video BG Palette]");
            #endif
            success = VideoRegisters::BGPaletteData(value);
            break;
        }
        case 0xFF50: {
            #ifdef DEBUG
            fprintf(debugStream, "[BOOT ROM Page]");
            #endif
            activeBootPage = &loadedRom;
            success = true;
            puts("Successfully reached end of boot rom");
            exit(0);
            break;
        }
        case 0xFF80 ... 0xFFFE: {
            int internalAddr = address - 0xFF80;
            #ifdef DEBUG
            fprintf(debugStream, " [Stack@%d]", internalAddr);
            #endif
            stack[internalAddr] = value;
            success = true;
            break;
        }
        UNIMPLEMENTED:
        default:printf(" (Unimplemented write range: 0x%04X)\n", address);
            exit(1);
    }
    #ifdef DEBUG
    fprintf(debugStream, " [VALUE 0x%02X]\n", value);
    fflush(debugStream);
    #endif
    return success;
}

void RAM::InitRam(ROM *rom)
{
    loadedRom = rom;
}

void RAM::SetDebugStream(FILE *stream)
{
    debugStream = stream;
}

void RAM::InitBootRom(ROM *boot)
{
    bootRom = boot;
}
