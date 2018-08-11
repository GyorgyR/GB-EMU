//
// Created by gyorgy on 11/08/18.
//

#ifndef GB_DISASSEMBLER_PROCESSOR_H
#define GB_DISASSEMBLER_PROCESSOR_H

#include <cstdint>

class Processor {
private:
    uint8_t* rom;
public:
    Processor(uint8_t* _rom);
    ~Processor();
    uint16_t  DecodeInstr(uint16_t address);

};


#endif //GB_DISASSEMBLER_PROCESSOR_H
