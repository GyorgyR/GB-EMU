//
// Created by gyorgy on 06/10/18.
//

#ifndef GB_EMULATOR_SOUNDGENERATOR_H
#define GB_EMULATOR_SOUNDGENERATOR_H

#include <cstdint>

class SoundGenerator
{
private:
    //Make it a non-instantiable static class
    SoundGenerator();

    ~SoundGenerator();

    static uint8_t soundOnOffReg;
    static uint8_t channel1WaveReg;
    static uint8_t channel1VolumeEnvelope;
    static uint8_t soundOutTerminalReg;
public:
    static uint8_t Channel1WavePattern();

    static bool ChannelWavePattern(uint8_t value);

    static uint8_t Channel1VolumeEnvelope();

    static bool Channel1VolumeEnvelope(uint8_t value);

    static uint8_t SoundOutTerminal();

    static bool SoundOutTerminal(uint8_t value);

    static uint8_t SoundOnOff();

    static bool SoundOnOff(uint8_t value);
};


#endif //GB_EMULATOR_SOUNDGENERATOR_H
