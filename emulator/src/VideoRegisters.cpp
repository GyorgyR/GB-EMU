//
// Created by gyorgy on 06/10/18.
//

#include "../include/VideoRegisters.h"
#include "../include/Helper.h"
#include "../include/Configuration.h"

uint8 VideoRegisters::BGPaletteDataReg = 0;
uint8 VideoRegisters::BGPaletteArray[4];
uint8 VideoRegisters::ScrollPosYReg = 0;
uint8 VideoRegisters::ScrollPosXReg = 0;
uint8 VideoRegisters::LCDControlReg = 0;
uint8 VideoRegisters::LCDYCoordReg = 0;

VideoRegisters::VideoRegisters()
{

}

VideoRegisters::~VideoRegisters()
{

}

uint8 VideoRegisters::BGPaletteData()
{
    return BGPaletteDataReg;
}

bool VideoRegisters::BGPaletteData(uint8_t value)
{
    BGPaletteDataReg = value;
    for (int pos = 0; pos < 4; ++pos) {
        BGPaletteArray[pos] = value & 0b11;
        value >>= 2;
    }
    return true;
}

uint8 VideoRegisters::ScrollPosY()
{
    return ScrollPosYReg;
}

bool VideoRegisters::ScrollPosY(uint8_t value)
{
    ScrollPosYReg = value;
    return true;
}

uint8 VideoRegisters::LCDControl()
{
    return LCDControlReg;
}

bool VideoRegisters::LCDControl(uint8_t value)
{
    LCDControlReg = value;
    return true;
}

uint16 VideoRegisters::BGTileMapBaseAddr()
{
    if (Helper::IsBitSet(LCDControlReg, 3)) return 0x9C00;
    else return 0x9800;
}

uint16 VideoRegisters::BGTileDataBaseAddr()
{
    if (Helper::IsBitSet(LCDControlReg, 4)) return 0x8000;
    else return 0x8800;
}

uint8 VideoRegisters::LCDYCoordinate()
{
    return LCDYCoordReg;
}

bool VideoRegisters::LCDYCoordinate(uint8 value)
{
    LCDYCoordReg = value;
    return true;
}

uint8 VideoRegisters::ScrollPosX()
{
    return ScrollPosXReg;
}

bool VideoRegisters::ScrollPosX(uint8 value)
{
    ScrollPosXReg = value;
    return true;
}

RGBA &VideoRegisters::GetBGColour(int colour) {
    return Configuration::Colours[BGPaletteArray[colour]];
}
