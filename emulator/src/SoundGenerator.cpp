//
// Created by gyorgy on 06/10/18.
//

#include "../include/SoundGenerator.h"

uint8 SoundGenerator::soundOnOffReg = 0xF1;
uint8 SoundGenerator::soundOutTerminalReg = 0xF3;
uint8 SoundGenerator::channelOnOffVolumeReg = 0x77;

uint8 SoundGenerator::channel1SweepReg = 0x80;
uint8 SoundGenerator::channel1WaveReg = 0xBF;
uint8 SoundGenerator::channel1VolumeEnvelope = 0xF3;
uint8 SoundGenerator::channel1FreqLoReg = 0;
uint8 SoundGenerator::channel1FreqHiReg = 0xBF;

uint8 SoundGenerator::channel2VolumeEnvelope = 0;
uint8 SoundGenerator::channel2FreqLoReg = 0;
uint8 SoundGenerator::channel2FreqHiReg = 0;

uint8 SoundGenerator::channel3OnOffReg = 0x7F;
uint8 SoundGenerator::channel3FreqLoReg = 0;
uint8 SoundGenerator::channel3FreqHiReg = 0;

uint8 SoundGenerator::channel4VolumeEnvelope = 0;
uint8 SoundGenerator::channel4CounterSelectReg = 0xBF;

SoundGenerator::SoundGenerator()
{

}

SoundGenerator::~SoundGenerator()
{

}

uint8 SoundGenerator::SoundOnOff()
{
    return soundOnOffReg;
}

bool SoundGenerator::SoundOnOff(uint8 value)
{
    soundOnOffReg = value;
    return true;
}

uint8 SoundGenerator::Channel1WavePattern()
{
    return channel1WaveReg;
}

bool SoundGenerator::Channel1WavePattern(uint8 value)
{
    channel1WaveReg = value;
    return true;
}

uint8 SoundGenerator::Channel1VolumeEnvelope()
{
    return channel1VolumeEnvelope;
}

bool SoundGenerator::Channel1VolumeEnvelope(uint8 value)
{
    channel1VolumeEnvelope = value;
    return true;
}

uint8 SoundGenerator::SoundOutTerminal()
{
    return soundOutTerminalReg;
}

bool SoundGenerator::SoundOutTerminal(uint8 value)
{
    soundOutTerminalReg = value;
    return true;
}

uint8 SoundGenerator::Channel1FreqLo()
{
    return channel1FreqLoReg;
}

bool SoundGenerator::Channel1FreqLo(uint8 value)
{
    channel1FreqLoReg = value;
    return true;
}

uint8 SoundGenerator::Channel1FreqHi()
{
    return channel1FreqHiReg;
}

bool SoundGenerator::Channel1FreqHi(uint8 value)
{
    channel1FreqHiReg = value;
    return true;
}

uint8 SoundGenerator::ChannelOnOffVolume()
{
    return channelOnOffVolumeReg;
}

bool SoundGenerator::ChannelOnOffVolume(uint8 value)
{
    channelOnOffVolumeReg = value;
    return true;
}

uint8 SoundGenerator::Channel2VolumeEnvelope()
{
    return channel2VolumeEnvelope;
}

bool SoundGenerator::Channel2VolumeEnvelope(uint8 value)
{
    channel2VolumeEnvelope = value;
    return true;
}

uint8 SoundGenerator::Channel4VolumeEnvelope()
{
    return channel4VolumeEnvelope;
}

bool SoundGenerator::Channel4VolumeEnvelope(uint8 value)
{
    channel4VolumeEnvelope = value;
    return true;
}

uint8 SoundGenerator::Channel2FreqLo()
{
    return channel2FreqLoReg;
}

bool SoundGenerator::Channel2FreqLo(uint8 value)
{
    channel2FreqLoReg = value;
    return true;
}

uint8 SoundGenerator::Channel2FreqHi()
{
    return channel2FreqHiReg;
}

bool SoundGenerator::Channel2FreqHi(uint8 value)
{
    channel2FreqHiReg = value;
    return true;
}

uint8 SoundGenerator::Channel3FreqLo()
{
    return channel3FreqLoReg;
}

bool SoundGenerator::Channel3FreqLo(uint8 value)
{
    channel3FreqLoReg = value;
    return true;
}

uint8 SoundGenerator::Channel3FreqHi()
{
    return channel3FreqHiReg;
}

bool SoundGenerator::Channel3FreqHi(uint8 value)
{
    channel3FreqHiReg = value;
    return true;
}

uint8 SoundGenerator::Channel4CounterSelect()
{
    return channel4CounterSelectReg;
}

bool SoundGenerator::Channel4CounterSelect(uint8 value)
{
    channel4CounterSelectReg = value;
    return true;
}

uint8 SoundGenerator::Channel1Sweep()
{
    return channel1SweepReg;
}

bool SoundGenerator::Channel1Sweep(uint8 value)
{
    channel1SweepReg = value;
    return true;
}

uint8 SoundGenerator::Channel3OnOff()
{
    return channel3OnOffReg;
}

bool SoundGenerator::Channel3OnOff(uint8 value)
{
    channel3OnOffReg = value;
    return true;
}
