//
// Created by gyorgy on 12/10/18.
//

#include "../include/RGBA.h"

RGBA::RGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) :
        r(_r), g(_g), b(_b), a(_a)
{
}

RGBA::RGBA(uint8_t _r, uint8_t _g, uint8_t _b) :
        r(_r), g(_g), b(_b), a(255)
{
}

RGBA::~RGBA()
{
}
