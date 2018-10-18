//
// Created by gyorgy on 06/10/18.
//

#ifndef GB_EMULATOR_VIDEOREGISTERS_H
#define GB_EMULATOR_VIDEOREGISTERS_H

#include <cstdint>
#include "Types.h"
#include "RGBA.h"

class VideoRegisters
{
private:
    //Make class static and non-instantiable
    VideoRegisters();
    ~VideoRegisters();

    static uint8 BGPaletteDataReg;
    static uint8 BGPaletteArray[];
    static uint8 ScrollPosYReg;
    static uint8 ScrollPosXReg;
    static uint8 LCDControlReg;
    static uint8 LCDYCoordReg;

public:
    static uint8 BGPaletteData();
    static bool BGPaletteData(uint8 value);
    static RGBA &GetBGColour(int colour);

    static uint8 ScrollPosY();
    static bool ScrollPosY(uint8 value);

    static uint8 ScrollPosX();
    static bool ScrollPosX(uint8 value);

    static uint8 LCDYCoordinate();
    static bool LCDYCoordinate(uint8 value);

    static uint8 LCDControl();
    static bool LCDControl(uint8 value);
    static uint16 BGTileMapBaseAddr();
    static uint16 BGTileDataBaseAddr();
};


#endif //GB_EMULATOR_VIDEOREGISTERS_H
