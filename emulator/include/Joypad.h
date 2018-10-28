//
// Created by gyorgy on 28/10/18.
//

#ifndef GB_EMULATOR_JOYPAD_H
#define GB_EMULATOR_JOYPAD_H


#include "Types.h"

class Joypad
{
private:
    //static class
    Joypad();
    ~Joypad();

    //Variables
    static bool  isDirectionKeys;
    static uint8 joypadReg;
    static uint8 *keyboardArray;

public:
    static bool  WriteToRegister(uint8 value);
    static uint8 ReadRegister();
};


#endif //GB_EMULATOR_JOYPAD_H
