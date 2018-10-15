//
// Created by gyorgy on 06/10/18.
//

#ifndef GB_EMULATOR_SOUNDGENERATOR_H
#define GB_EMULATOR_SOUNDGENERATOR_H

#include <cstdint>
#include "Types.h"

class SoundGenerator
{
private:
    //Make it a non-instantiable static class
    SoundGenerator();

    ~SoundGenerator();

    static uint8 soundOnOffReg;
    static uint8 channel1WaveReg;
    static uint8 channel1VolumeEnvelope;
    static uint8 soundOutTerminalReg;
    static uint8 channel1FreqLoReg;
    static uint8 channel1FreqHiReg;
public:
    static uint8 Channel1WavePattern();

    static bool Channel1WavePattern(uint8 value);

    static uint8 Channel1FreqLo();

    static bool Channel1FreqLo(uint8 value);

    static uint8 Channel1FreqHi();

    static bool Channel1FreqHi(uint8 value);

    static uint8 Channel1VolumeEnvelope();

    static bool Channel1VolumeEnvelope(uint8 value);

    static uint8 SoundOutTerminal();

    static bool SoundOutTerminal(uint8 value);

    static uint8 SoundOnOff();

    static bool SoundOnOff(uint8 value);
};


#endif //GB_EMULATOR_SOUNDGENERATOR_H
