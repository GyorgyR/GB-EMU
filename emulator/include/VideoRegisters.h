//
// Created by gyorgy on 06/10/18.
//

#ifndef GB_EMULATOR_VIDEOREGISTERS_H
#define GB_EMULATOR_VIDEOREGISTERS_H

#include <cstdint>

class VideoRegisters
{
private:
    //Make class static and non-instantiable
    VideoRegisters();
    ~VideoRegisters();

    static uint8_t BGPaletteDataReg;
    static uint8_t ScrollPosYReg;
    static uint8_t LCDControlReg;

public:
    static uint8_t BGPaletteData();
    static bool    BGPaletteData(uint8_t value);

    static uint8_t ScrollPosY();
    static bool    ScollPosY(uint8_t value);

    static uint8_t LCDControl();
    static bool    LCDControl(uint8_t value);
};


#endif //GB_EMULATOR_VIDEOREGISTERS_H
