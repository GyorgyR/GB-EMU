//
// Created by gyorgy on 27/10/18.
//

#include <cstdlib>

#include "../include/Timer.h"
#include "../include/Helper.h"
#include "../include/RegisterBank.h"
#include "../include/EventMiddleware.h"

uint8 Timer::dividerReg = 0;
uint8 Timer::timerCounterReg = 0;
uint8 Timer::timerModuloReg = 0;
uint8 Timer::timerControlReg = 0;

bool Timer::isRunning = false;
int  Timer::cyclesBeforeIncrement = 0;
int  Timer::cyclesPassed = 0;
int  Timer::divCyclesPassed = 0;

const int CLOCKSPEED = 4194304;

Timer::Timer() {}

Timer::~Timer() {}

uint8 Timer::Divider()
{
    return dividerReg;
}

bool Timer::Divider(uint8)
{
    dividerReg = 0;
    return true;
}

uint8 Timer::TimerCounter()
{
    return timerCounterReg;
}

bool Timer::TimerCounter(uint8 value)
{
    timerCounterReg = value;
    return true;
}

uint8 Timer::TimerModulo()
{
    return timerModuloReg;
}

bool Timer::TimerModulo(uint8 value)
{
    timerModuloReg = value;
    return true;
}

uint8 Timer::TimerControl()
{
    return timerControlReg;
}

bool Timer::TimerControl(uint8 value)
{
    isRunning = value & 0b100;
    if (isRunning) EventMiddleware::SubscribeToCpuCyclesPassed(Timer::Update);
    else EventMiddleware::UnsubscribeFromCpuCyclesPassed(Timer::Update);

    switch (value & 0b11) {
        case 0b00: cyclesBeforeIncrement = CLOCKSPEED / 4096;
            break;
        case 0b01: cyclesBeforeIncrement = CLOCKSPEED / 262144;
            break;
        case 0b10: cyclesBeforeIncrement = CLOCKSPEED / 65536;
            break;
        case 0b11: cyclesBeforeIncrement = CLOCKSPEED / 16384;
            break;
        default:Helper::Log("Invalid timer clock");
            exit(1);
    }

    timerControlReg = value;
    return true;
}

void Timer::Update(int cycles)
{
    if (!isRunning) return;

    cyclesPassed += cycles;

    if (cyclesPassed >= cyclesBeforeIncrement) {
        cyclesPassed -= cyclesBeforeIncrement;
        ++timerCounterReg;

        if (timerCounterReg == 0) {
            timerCounterReg = timerModuloReg;

            //Request interrupt
            RegisterBank::SetBitInIF(2);
        }
    }

    divCyclesPassed += cycles;

    if (divCyclesPassed >= CLOCKSPEED / 16384) {
        divCyclesPassed -= CLOCKSPEED / 16384;
        ++dividerReg;
    }
}
