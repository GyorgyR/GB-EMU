//
// Created by gyorgy on 17/09/18.
//

#ifndef GB_EMULATOR_REGISTERBANK_H
#define GB_EMULATOR_REGISTERBANK_H

#include <cstdint>


class RegisterBank {
public:
    static uint8_t A;
    static uint8_t F;
    static uint8_t B;
    static uint8_t C;
    static uint8_t D;
    static uint8_t E;
    static uint8_t H;
    static uint8_t L;

    static uint16_t SP;
    static uint16_t PC;

    static bool IsZSet();
    static bool IsCSet();
    static bool IsNSet();
    static bool IsHSet();

    static void SetZ(bool isOn);
    static void SetC(bool isOn);
    static void SetN(bool isOn);
    static void SetH(bool isOn);

    static uint16_t AF();
    static uint16_t BC();
    static uint16_t DE();
    static uint16_t HL();

    static void AF(uint16_t value);
    static void BC(uint16_t value);
    static void DE(uint16_t value);
    static void HL(uint16_t value);
};


#endif //GB_EMULATOR_REGISTERBANK_H
