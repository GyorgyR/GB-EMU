//
// Created by gyorgy on 19/09/18.
//

#define DEBUG
#undef RAM_DEBUG
#undef PPU_DEBUG
#undef CPU_DEBUG

#include <cstdio>
#include <cstdarg>

#include "../include/Helper.h"

FILE *Helper::debugLog;
FILE *Helper::ramLog;
FILE *Helper::cpuLog;
FILE *Helper::ppuLog;

Helper::Helper()
{

}

Helper::~Helper()
{

}

uint16_t Helper::ConcatTwoBytes(uint8_t first, uint8_t second) {
    return (first << 8) + second;
}

std::pair<uint8_t, uint8_t> Helper::DivideIntoTwoBytes(uint16_t value) {
    const uint16_t bit_mask = 0b0000000011111111;
    return std::make_pair((value >> 8) & bit_mask, value & bit_mask);
}

bool Helper::IsBitSet(uint16_t bits, uint16_t bitPos)
{
    uint16_t bitmask = 1 << bitPos;
    return bits & bitmask;
}

void Helper::InitLogger()
{
    debugLog = fopen("logs/debug.log", "w+");
    ramLog = fopen("logs/ram.debug.log", "w+");
    cpuLog = fopen("logs/cpu.debug.log", "w+");
    ppuLog = fopen("logs/ppu.debug.log", "w+");
}

void Helper::Log(const char *message, ...)
{
    #ifdef DEBUG
    va_list args;
    va_start(args, message);
    vfprintf(debugLog, message, args);
    va_end(args);
    fprintf(debugLog, "\n");
    fflush(debugLog);
    #else
    return;
    #endif
}

void Helper::SetCPULogStream(FILE *stream)
{
    cpuLog = stream;
}

void Helper::CPULog(const char *message, ...)
{
    #ifdef CPU_DEBUG
    va_list args;
    va_start(args, message);
    vfprintf(cpuLog, message, args);
    va_end(args);
    fflush(cpuLog);
    #else
    return;
    #endif
}

void Helper::RAMLog(const char *message, ...)
{
    #ifdef RAM_DEBUG
    va_list args;
    va_start(args, message);
    vfprintf(ramLog, message, args);
    va_end(args);
    fflush(ramLog);
    #else
    return;
    #endif
}

void Helper::PPULog(const char *message, ...)
{
    #ifdef PPU_DEBUG
    va_list args;
    va_start(args, message);
    vfprintf(ppuLog, message, args);
    va_end(args);
    fflush(ppuLog);
    #else
    return;
    #endif
}
