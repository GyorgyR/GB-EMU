//
// Created by gyorgy on 12/10/18.
//

#ifndef GB_EMULATOR_CONFIGURATION_H
#define GB_EMULATOR_CONFIGURATION_H

#include <string>

#include "RGBA.h"

class Configuration
{
private:
    //Make class static
    Configuration();

    ~Configuration();
public:
    static std::string WindowTitle;
    static unsigned int PixelScaleFactor;
    static RGBA Colours[];
};


#endif //GB_EMULATOR_CONFIGURATION_H
