//
// Created by gyorgy on 12/10/18.
//

#ifndef GB_EMULATOR_RGBA_H
#define GB_EMULATOR_RGBA_H


#include <cstdint>

class RGBA
{
public:
    RGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a);

    RGBA(uint8_t _r, uint8_t _g, uint8_t _b);

    ~RGBA();

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};


#endif //GB_EMULATOR_RGBA_H
