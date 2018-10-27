//
// Created by gyorgy on 17/09/18.
//

#ifndef GB_EMULATOR_REGISTERBANK_H
#define GB_EMULATOR_REGISTERBANK_H

#include <cstdint>
#include "Types.h"


class RegisterBank {
private:
    //Make class static
    RegisterBank();
    ~RegisterBank();

    static uint8 interruptFlag;
    static uint8 interruptEnable;
    static bool areInterruptsEnabled;

public:
    static uint8 A;
    static uint8 F;
    static uint8 B;
    static uint8 C;
    static uint8 D;
    static uint8 E;
    static uint8 H;
    static uint8 L;

    static uint16 SP;
    static uint16 PC;

    static bool IsZSet();
    static bool IsCSet();
    static bool IsNSet();
    static bool IsHSet();

    static void SetZ(bool isOn);
    static void SetC(bool isOn);
    static void SetN(bool isOn);
    static void SetH(bool isOn);

    static uint16 AF();
    static uint16 BC();
    static uint16 DE();
    static uint16 HL();

    static void AF(uint16 value);
    static void BC(uint16 value);
    static void DE(uint16 value);
    static void HL(uint16 value);

    static bool AreInterruptsEnabled();
    static void SetInterruptEnabled(bool enabled);

    static uint8 InterruptFlag();
    static void  InterruptFlag(uint8 value);
    static uint8 InterruptEnable();
    static void  InterruptEnable(uint8 value);
};


#endif //GB_EMULATOR_REGISTERBANK_H
