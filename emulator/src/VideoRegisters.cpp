//
// Created by gyorgy on 06/10/18.
//

#include "../include/VideoRegisters.h"

uint8_t VideoRegisters::BGPaletteDataReg = 0;

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


