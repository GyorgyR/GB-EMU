//
// Created by gyorgy on 06/10/18.
//

#include "../include/VideoRegisters.h"
#include "../include/Helper.h"
#include "../include/Configuration.h"

uint8 VideoRegisters::BGPaletteDataReg = 0xFC;
uint8 VideoRegisters::BGPaletteArray[4];
uint8 VideoRegisters::OBJPalette0Reg = 0xFF;
uint8 VideoRegisters::OBJPalette0Array[4];
uint8 VideoRegisters::OBJPalette1Reg = 0xFF;
uint8 VideoRegisters::OBJPalette1Array[4];
uint8 VideoRegisters::ScrollPosYReg = 0;
uint8 VideoRegisters::ScrollPosXReg = 0;
uint8 VideoRegisters::LCDControlReg = 0x91;
uint8 VideoRegisters::LCDYCoordReg = 0;
uint8 VideoRegisters::LCDStatReg = 0;
uint8 VideoRegisters::WindowPosYReg = 0;
uint8 VideoRegisters::WindowPosXReg = 0;
uint8 VideoRegisters::OAMRam[160];
bool VideoRegisters::IsWindowEnabled = false;

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

bool VideoRegisters::BGPaletteData(uint8 value)
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

bool VideoRegisters::ScrollPosY(uint8 value)
{
    ScrollPosYReg = value;
    return true;
}

uint8 VideoRegisters::LCDControl()
{
    return LCDControlReg;
}

bool VideoRegisters::LCDControl(uint8 value)
{
    IsWindowEnabled = Helper::IsBitSet(value, 5);
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
    Helper::Log("Current X Scroll: %d", value);
    return true;
}

RGBA &VideoRegisters::GetBGColour(int colour) {
    return Configuration::Colours[BGPaletteArray[colour]];
}

uint8 VideoRegisters::LCDStat() {
    return LCDStatReg;
}

bool VideoRegisters::LCDStat(uint8 value) {
    uint8 originalLower = value & 0b111;
    LCDStatReg = value & 0b000;
    LCDStatReg |= originalLower;
    return true;
}

uint8 VideoRegisters::OBJPalette0Data() {
    return OBJPalette0Reg;
}

bool VideoRegisters::OBJPalette0Data(uint8 value) {
    OBJPalette0Reg = value;
    for (int pos = 0; pos < 4; ++pos) {
        OBJPalette0Array[pos] = value & 0b11;
        value >>= 2;
    }
    return true;
}

RGBA &VideoRegisters::GetObjColour0(int colour) {
    return Configuration::Colours[OBJPalette0Array[colour]];
}

uint8 VideoRegisters::OBJPalette1Data() {
    return OBJPalette1Reg;
}

bool VideoRegisters::OBJPalette1Data(uint8 value) {
    OBJPalette1Reg = value;
    for (int pos = 0; pos < 4; ++pos) {
        OBJPalette1Array[pos] = value & 0b11;
        value >>= 2;
    }
    return true;
}

RGBA &VideoRegisters::GetObjColour1(int colour) {
    return Configuration::Colours[OBJPalette1Array[colour]];
}

void VideoRegisters::LCDStatMode(uint8 value) {
    LCDStatReg &= 0b00;
    LCDStatReg |= value & 0b11;
}

uint8 VideoRegisters::WindowPosY()
{
    return WindowPosYReg;
}

bool VideoRegisters::WindowPosY(uint8 value)
{
    WindowPosYReg = value;
    return true;
}

uint8 VideoRegisters::WindowPosX()
{
    return WindowPosXReg;
}

bool VideoRegisters::WindowPosX(uint8 value)
{
    WindowPosXReg = value;
    return true;
}
