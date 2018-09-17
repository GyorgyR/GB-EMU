//
// Created by gyorgy on 11/08/18.
//

#ifndef GB_DISASSEMBLER_PROCESSOR_H
#define GB_DISASSEMBLER_PROCESSOR_H

#include <cstdint>

class Processor {
private:
    int DecodeInstr(uint16_t address);
public:
    Processor();
    ~Processor();
    void StartCPULoop();
};


#endif //GB_DISASSEMBLER_PROCESSOR_H
