//
// Created by gyorgy on 06/10/18.
//

#ifndef GB_EMULATOR_VIDEOREGISTERS_H
#define GB_EMULATOR_VIDEOREGISTERS_H

#include <cstdint>
#include "Types.h"
#include "RGBA.h"

struct OAMEntry
{
    uint8 PosY;
    uint8 PosX;
    uint8 SpriteNo;
    bool  Priority;
    bool  FlipY;
    bool  FlipX;
    bool  PaletteSelect;
};

class VideoRegisters
{
private:
    //Make class static and non-instantiable
    VideoRegisters();
    ~VideoRegisters();

    static uint8 BGPaletteDataReg;
    static uint8 BGPaletteArray[];
    static uint8 OBJPalette0Reg;
    static uint8 OBJPalette0Array[];
    static uint8 OBJPalette1Reg;
    static uint8 OBJPalette1Array[];
    static uint8 ScrollPosYReg;
    static uint8 ScrollPosXReg;
    static uint8 LCDControlReg;
    static uint8 LCDYCoordReg;
    static uint8 LCDStatReg;
    static uint8 WindowPosYReg;
    static uint8 WindowPosXReg;
    static uint8 OAMRamArray[];

public:
    //Variables
    static bool IsWindowEnabled;
    static OAMEntry OAMEntyArray[];

    //Methods
    static uint8 BGPaletteData();
    static bool  BGPaletteData(uint8 value);
    static RGBA &GetBGColour(int colour);

    static uint8 OBJPalette0Data();
    static bool  OBJPalette0Data(uint8 value);
    static RGBA &GetObjColour0(int colour);

    static uint8 OBJPalette1Data();
    static bool  OBJPalette1Data(uint8 value);
    static RGBA &GetObjColour1(int colour);

    static uint8 ScrollPosY();
    static bool  ScrollPosY(uint8 value);

    static uint8 ScrollPosX();
    static bool  ScrollPosX(uint8 value);

    static uint8 LCDYCoordinate();
    static bool  LCDYCoordinate(uint8 value);

    static uint8 LCDControl();
    static bool  LCDControl(uint8 value);

    static uint16 BGTileMapBaseAddr();
    static uint16 BGTileDataBaseAddr();

    static uint8 LCDStat();
    static bool  LCDStat(uint8 value);
    static void  LCDStatMode(uint8 value);

    static uint8 WindowPosY();
    static bool  WindowPosY(uint8 value);

    static uint8 WindowPosX();
    static bool  WindowPosX(uint8 value);

    static uint8 OAMRam(uint8 address);
    static bool  OAMRam(uint8 address, uint8 value);
};


#endif //GB_EMULATOR_VIDEOREGISTERS_H
