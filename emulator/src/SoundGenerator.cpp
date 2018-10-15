//
// Created by gyorgy on 06/10/18.
//

#include "../include/SoundGenerator.h"

uint8_t SoundGenerator::soundOnOffReg = 0;
uint8_t SoundGenerator::channel1WaveReg = 0;
uint8_t SoundGenerator::channel1VolumeEnvelope = 0;
uint8_t SoundGenerator::soundOutTerminalReg = 0;
uint8_t SoundGenerator::channel1FreqLoReg = 0;
uint8_t SoundGenerator::channel1FreqHiReg = 0;

SoundGenerator::SoundGenerator()
{

}

SoundGenerator::~SoundGenerator()
{

}

uint8_t SoundGenerator::SoundOnOff()
{
    return soundOnOffReg;
}

bool SoundGenerator::SoundOnOff(uint8_t value)
{
    soundOnOffReg = value;
    return true;
}

uint8_t SoundGenerator::Channel1WavePattern()
{
    return channel1WaveReg;
}

bool SoundGenerator::Channel1WavePattern(uint8_t value)
{
    channel1WaveReg = value;
    return true;
}

uint8_t SoundGenerator::Channel1VolumeEnvelope()
{
    return channel1VolumeEnvelope;
}

bool SoundGenerator::Channel1VolumeEnvelope(uint8_t value)
{
    channel1VolumeEnvelope = value;
    return true;
}

uint8_t SoundGenerator::SoundOutTerminal()
{
    return soundOutTerminalReg;
}

bool SoundGenerator::SoundOutTerminal(uint8_t value)
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
