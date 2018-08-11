//
// Created by gyorgy on 11/08/18.
//

#include "Processor.h"

Processor::~Processor()
{
}

Processor::Processor(uint8_t* _rom) : rom(_rom)
{
}

uint16_t Processor::DecodeInstr(uint16_t address)
{
    uint8_t op_code = rom[address];
    return 0;
}
