//
// Created by gyorgy on 19/09/18.
//

#define DEBUG

#include <cstdio>
#include <cstdarg>

#include "../include/Helper.h"

FILE *Helper::debugLog;
FILE *Helper::ramLog;
FILE *Helper::cpuLog;

uint16_t Helper::ConcatTwoBytes(uint8_t first, uint8_t second) {
    return (first << 8) + second;
}

std::pair<uint8_t, uint8_t> Helper::DivideIntoTwoBytes(uint16_t value) {
    const uint16_t bit_mask = 0b0000000011111111;
    return std::make_pair((value >> 8) & bit_mask, value & bit_mask);
}

Helper::Helper()
{

}

Helper::~Helper()
{

}

void Helper::InitLogger()
{
    #ifdef DEBUG
    debugLog = fopen("logs/debug.log", "w+");
    ramLog = fopen("logs/ram.debug.log", "w+");
    cpuLog = fopen("logs/cpu.debug.log", "w+");
    #else
    return
    #endif
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

void Helper::CPULog(const char *message, ...)
{
    #ifdef DEBUG
    va_list args;
    va_start(args, message);
    vfprintf(cpuLog, message, args);
    va_end(args);
    fprintf(cpuLog, "\n");
    fflush(cpuLog);
    #else
    return;
    #endif
}

void Helper::RAMLog(const char *message, ...)
{
    #ifdef DEBUG
    va_list args;
    va_start(args, message);
    vfprintf(ramLog, message, args);
    va_end(args);
    fprintf(ramLog, "\n");
    fflush(ramLog);
    #else
    return
    #endif
}
