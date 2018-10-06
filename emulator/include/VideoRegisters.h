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
public:
    static uint8_t BGPaletteData();

    static bool BGPaletteData(uint8_t value);
};


#endif //GB_EMULATOR_VIDEOREGISTERS_H
