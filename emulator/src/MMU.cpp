//
// Created by gyorgy on 29/09/18.
//

#include <cstdlib>
#include <cstdio>

#include "../include/MMU.h"
#include "../include/SoundGenerator.h"
#include "../include/VideoRegisters.h"
#include "../include/Helper.h"
#include "../include/Types.h"
#include "../include/RegisterBank.h"
#include "../include/Timer.h"
#include "../include/Joypad.h"
#include "../include/DMA.h"

ROM *MMU::loadedRom = nullptr;
ROM *MMU::bootRom = nullptr;
ROM **MMU::activeBootPage = &bootRom;
uint8 MMU::vram[8192];
uint8 MMU::stack[0x7F];
uint8 MMU::workRam[8][4096];
uint8 MMU::romBankNo = 1;
uint8 MMU::wramBankNo = 1;

MMU::MMU()
{
}

MMU::~MMU()
{
}

uint8 MMU::ReadByteAt(uint16 address)
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
            uint16 switchedAddress = address + (romBankNo - 1) * (0x7FFF - 0x4000);
            retVal = loadedRom->GetByteAt(switchedAddress);
            Helper::RAMLog("[ROM BANK %d]", romBankNo);
            break;
        }
        case 0x8000 ... 0x9FFF: {
            int internalAddress = address - 0x8000;
            Helper::RAMLog(" [VRAM@%d]", internalAddress);
            retVal = vram[internalAddress];
            break;
        }
        case 0xC000 ... 0xCFFF: {
            int internalAddress = address - 0xC000;
            Helper::RAMLog(" [WRAM0@d]", internalAddress);
            retVal = workRam[0][internalAddress];
            break;
        }
        case 0xD000 ... 0xDFFF : {
            int intenalAddress = address - 0xD000;
            Helper::RAMLog(" [WRAM1%d]", intenalAddress);
            retVal = workRam[wramBankNo][intenalAddress];
            break;
        }
        case 0xFF00: {
            Helper::RAMLog(" [Joypad Register]");
            retVal = Joypad::ReadRegister();
            break;
        }
        case 0xFF24: {
            Helper::RAMLog(" [Channel ctrl/on-off]");
            retVal = SoundGenerator::ChannelOnOffVolume();
            break;
        }
        case 0xFF42: {
            Helper::RAMLog(" [ScrollPosY]");
            retVal = VideoRegisters::ScrollPosY();
            break;
        }
        case 0xFF40: {
            Helper::RAMLog(" [LCDControl]");
            retVal = VideoRegisters::LCDControl();
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
        case 0xFFFF: {
            Helper::RAMLog(" [Interrupt Enable]");
            retVal = RegisterBank::InterruptEnable();
            break;
        }
        default:
            printf(" (Unimplemented read range: 0x%04X)\n", address);
            exit(1);
    }
    Helper::RAMLog(" [VALUE 0x%02X]\n", retVal);
    return retVal;
}

bool MMU::WriteByteAt(uint16 address, uint8 value)
{
    Helper::RAMLog("[WRITE] [@0x%04X]", address);
    bool success = false;
    switch (address) {
        case 0x2000 ... 0x3FFF: {
            romBankNo = value & 0b11111;
            success = true;
            break;
        }
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
            workRam[wramBankNo][intenalAddress] = value;
            success = true;
            break;
        }
        case 0xFE00 ... 0xFE9F: {
            int internalAddress = address - 0xFE00;
            Helper::RAMLog(" [OAM@%d]", internalAddress);
            VideoRegisters::OAMRam[internalAddress] = value;
            success = true;
            break;
        }
        case 0xFEA0 ... 0xFEFF: {
            success = false;
            break;
        }
        case 0xFF00: {
            Helper::RAMLog(" [Joypad Register]");
            success = Joypad::WriteToRegister(value);
            break;
        }
        case 0xFF01: {
            Helper::RAMLog(" [Serial Data]");
            printf("Serial send data: 0x%02X\n", value);
            success = false;
            break;
        }
        case 0xFF02: {
            Helper::RAMLog(" [Serial Control");
            printf("Serial set control: 0x%02X\n", value);
            success = false;
            break;
        }
        case 0xFF06: {
            Helper::RAMLog(" [Timer Modulo]");
            success = Timer::TimerModulo(value);
            break;
        }
        case 0xFF07: {
            Helper::RAMLog(" [Timer Control]");
            success = Timer::TimerControl(value);
            break;
        }
        case 0xFF0F: {
            Helper::RAMLog(" [Interrupt Flag]");
            RegisterBank::InterruptFlag(value);
            success = true;
            break;
        }
        case 0xFF10: {
            Helper::RAMLog(" [Channel1 Sweep]");
            success = SoundGenerator::Channel1Sweep(value);
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
        case 0xFF17: {
            Helper::RAMLog(" [Chanel2 Volume Envelope]");
            success = SoundGenerator::Channel2VolumeEnvelope(value);
            break;
        }
        case 0xFF19: {
            Helper::RAMLog(" [Channel2 Freq-hi]");
            success = SoundGenerator::Channel2FreqHi(value);
            break;
        }
        case 0xFF1A: {
            Helper::RAMLog(" [Channel3 On/Off]");
            success = SoundGenerator::Channel3OnOff(value);
            break;
        }
        case 0xFF21: {
            Helper::RAMLog(" [Channel4 Volume Envelope]");
            success = SoundGenerator::Channel4VolumeEnvelope(value);
            break;
        }
        case 0xFF23: {
            Helper::RAMLog(" [Channel4 Counter/Consecutive Select]");
            success = SoundGenerator::Channel4CounterSelect(value);
            break;
        }
        case 0xFF24: {
            Helper::RAMLog(" [Channel Control]");
            success = SoundGenerator::ChannelOnOffVolume(value);
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
        case 0xFF41: {
            Helper::RAMLog(" [LCD STAT]");
            success = VideoRegisters::LCDStat(value);
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
        case 0xFF46: {
            Helper::RAMLog(" [DMA@0x%04X]", value * 0x100);
            success = DMA::Start(value);
            break;
        }
        case 0xFF47: {
            Helper::RAMLog(" [Video BG Palette]");
            success = VideoRegisters::BGPaletteData(value);
            break;
        }
        case 0xFF48: {
            Helper::RAMLog(" [Video OBJ Palette0]");
            success = VideoRegisters::OBJPalette0Data(value);
            break;
        }
        case 0xFF49: {
            Helper::RAMLog(" [Video OBJ Palette1]");
            success = VideoRegisters::OBJPalette1Data(value);
            break;
        }
        case 0xFF4A: {
            Helper::RAMLog(" [Window Y Pos]");
            success = VideoRegisters::WindowPosY(value);
            break;
        }
        case 0xFF4B: {
            Helper::RAMLog(" [Window X Pos]");
            success = VideoRegisters::WindowPosX(value);
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
        case 0xFF7F: {
            success = false;
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
            RegisterBank::InterruptEnable(value);
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

void MMU::InitRam(ROM *rom)
{
    loadedRom = rom;
}

void MMU::InitBootRom(ROM *boot)
{
    bootRom = boot;
}

void MMU::DumpVRAM()
{
    for (int i = 0x8000; i < 0xA000; ++i) {
        Helper::Log("0x%04X: 0x%02X", i, vram[i - 0x8000]);
    }
}

void MMU::DisableBootrom()
{
    activeBootPage = &loadedRom;
}


