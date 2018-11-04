//
// Created by gyorgy on 11/08/18.
//

#ifndef GB_DISASSEMBLER_PROCESSOR_H
#define GB_DISASSEMBLER_PROCESSOR_H

#include "Types.h"

class Processor {
private:
    int decodeInstr(uint16 address);

public:
    Processor();
    ~Processor();
    void StartCPULoop();
};


#endif //GB_DISASSEMBLER_PROCESSOR_H
