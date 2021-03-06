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

    //The registers
    static uint8 soundOnOffReg;
    static uint8 soundOutTerminalReg;
    static uint8 channelOnOffVolumeReg;

    //Channel 1
    static uint8 channel1SweepReg;
    static uint8 channel1SoundLengthReg;
    static uint8 channel1VolumeEnvelope;
    static uint8 channel1FreqLoReg;
    static uint8 channel1FreqHiReg;

    //Channel 2
    static uint8 channel2SoundLengthReg;
    static uint8 channel2VolumeEnvelope;
    static uint8 channel2FreqLoReg;
    static uint8 channel2FreqHiReg;

    //Channel 3
    static uint8 channel3OnOffReg;
    static uint8 channel3SoundLengthReg;
    static uint8 channel3SelectOutLevel;
    static uint8 channel3FreqLoReg;
    static uint8 channel3FreqHiReg;

    //Channel 4
    static uint8 channel4SoundLengthReg;
    static uint8 channel4VolumeEnvelope;
    static uint8 channel4PolyCounterReg;
    static uint8 channel4CounterSelectReg;

public:
    //Channel 1
    static uint8 Channel1Sweep();
    static bool  Channel1Sweep(uint8 value);
    static uint8 Channel1SoundLength();
    static bool  Channel1SoundLength(uint8 value);
    static uint8 Channel1FreqLo();
    static bool  Channel1FreqLo(uint8 value);
    static uint8 Channel1FreqHi();
    static bool  Channel1FreqHi(uint8 value);
    static uint8 Channel1VolumeEnvelope();
    static bool  Channel1VolumeEnvelope(uint8 value);

    //Channel 2
    static uint8 Channel2SoundLength();
    static bool  Channel2SoundLength(uint8 value);
    static uint8 Channel2VolumeEnvelope();
    static bool  Channel2VolumeEnvelope(uint8 value);
    static uint8 Channel2FreqLo();
    static bool  Channel2FreqLo(uint8 value);
    static uint8 Channel2FreqHi();
    static bool  Channel2FreqHi(uint8 value);

    //Channel 3
    static uint8 Channel3OnOff();
    static bool  Channel3OnOff(uint8 value);
    static uint8 Channel3SoundLength();
    static bool  Channel3SoundLength(uint8 value);
    static uint8 Channel3OutLevel();
    static bool  Channel3OutLevel(uint8 value);
    static uint8 Channel3FreqLo();
    static bool  Channel3FreqLo(uint8 value);
    static uint8 Channel3FreqHi();
    static bool  Channel3FreqHi(uint8 value);
    static uint8 channel3WaveRAM[];

    //Channel 4
    static uint8 Channel4SoundLength();
    static bool  Channel4SoundLength(uint8 value);
    static uint8 Channel4VolumeEnvelope();
    static bool  Channel4VolumeEnvelope(uint8 value);
    static uint8 Channel4PolyCounter();
    static bool  Channel4PolyCounter(uint8 value);
    static uint8 Channel4CounterSelect();
    static bool  Channel4CounterSelect(uint8 value);

    //Misc
    static uint8 SoundOutTerminal();
    static bool SoundOutTerminal(uint8 value);

    static uint8 SoundOnOff();
    static bool SoundOnOff(uint8 value);

    static uint8 ChannelOnOffVolume();
    static bool ChannelOnOffVolume(uint8 value);
};


#endif //GB_EMULATOR_SOUNDGENERATOR_H
