//
// Created by gyorgy on 19/09/18.
//

#ifndef GB_EMULATOR_HELPER_H
#define GB_EMULATOR_HELPER_H

#include <utility>
#include <cstdint>
#include <fstream>

#include "ROM.h"

using std::ofstream;

class Helper {
private:
    Helper();

    ~Helper();

    static ofstream debugLog;
public:
    static uint16_t ConcatTwoBytes(uint8_t first, uint8_t second);
    static std::pair<uint8_t, uint8_t> DivideIntoTwoBytes(uint16_t value);

    static void InitLogger();

    static void Log(const std::string message);
};


#endif //GB_EMULATOR_HELPER_H
