//
// Created by gyorgy on 19/09/18.
//

#ifndef GB_EMULATOR_HELPER_H
#define GB_EMULATOR_HELPER_H

#include <utility>
#include <cstdint>
#include <cstdio>

#include "ROM.h"

class Helper {
private:
    Helper();

    ~Helper();

    static FILE *debugLog;
    static FILE *ramLog;
    static FILE *cpuLog;
    static FILE *ppuLog;
public:
    static uint16_t ConcatTwoBytes(uint8_t first, uint8_t second);
    static std::pair<uint8_t, uint8_t> DivideIntoTwoBytes(uint16_t value);

    static bool IsBitSet(uint16 bits, uint16 bitPos);
    static void ClearBit(uint16 *bits, uint16 bitPos);
    static void ClearBit(uint8 *bits, uint8 bitPos);

    static void SetBit(uint8 *bits, uint8 bitPos);

    static void InitLogger();

    static void Log(const char *message, ...);

    static void SetCPULogStream(FILE *stream);
    static void CPULog(const char *message, ...);

    static void PPULog(const char *message, ...);

    static void RAMLog(const char *message, ...);
};


#endif //GB_EMULATOR_HELPER_H
