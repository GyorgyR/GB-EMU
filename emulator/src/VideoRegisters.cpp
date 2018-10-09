//
// Created by gyorgy on 06/10/18.
//

#include "../include/VideoRegisters.h"

uint8_t VideoRegisters::BGPaletteDataReg = 0;
uint8_t VideoRegisters::ScrollPosYReg = 0;
uint8_t VideoRegisters::LCDControlReg = 0;

VideoRegisters::VideoRegisters()
{

}

VideoRegisters::~VideoRegisters()
{

}

uint8_t VideoRegisters::BGPaletteData()
{
    return BGPaletteDataReg;
}

bool VideoRegisters::BGPaletteData(uint8_t value)
{
    BGPaletteDataReg = value;
    return true;
}

uint8_t VideoRegisters::ScrollPosY()
{
    return ScrollPosYReg;
}

bool VideoRegisters::ScollPosY(uint8_t value)
{
    ScrollPosYReg = value;
    return true;
}

uint8_t VideoRegisters::LCDControl()
{
    return LCDControlReg;
}

bool VideoRegisters::LCDControl(uint8_t value)
{
    LCDControlReg = value;
    return true;
}
