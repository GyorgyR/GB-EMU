//
// Created by gyorgy on 11/08/18.
//

#ifndef GB_DISASSEMBLER_DECODER_H
#define GB_DISASSEMBLER_DECODER_H

#include <cstdint>

class Decoder {
private:
    uint8_t* rom;
public:
    Decoder(uint8_t* _rom);
    ~Decoder();
    int  DecodeInstr(uint16_t address);

};


#endif //GB_DISASSEMBLER_DECODER_H
