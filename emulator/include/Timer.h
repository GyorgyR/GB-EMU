//
// Created by gyorgy on 27/10/18.
//

#ifndef GB_EMULATOR_TIMER_H
#define GB_EMULATOR_TIMER_H


#include "Types.h"

class Timer
{
private:
    //Make class static
    Timer();

    ~Timer();

    //Registers
    static uint8 dividerReg;
    static uint8 timerCounterReg;
    static uint8 timerModuloReg;
    static uint8 timerControlReg;

    //Variables
    static bool isRunning;
    static int cyclesBeforeIncrement;
    static int cyclesPassed;

public:
    //Getters and setters
    static uint8 Divider();

    static bool Divider();

    static uint8 TimerCounter();

    static bool TimerCounter(uint8 value);

    static uint8 TimerModulo();

    static bool TimerModulo(uint8 value);

    static uint8 TimerControl();

    static bool TimerControl(uint8 value);

    static void Update(int cycles);
};


#endif //GB_EMULATOR_TIMER_H
