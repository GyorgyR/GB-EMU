//
// Created by gyorgy on 07/10/18.
//
#include <cstdint>
#include <cstdio>

#include "../include/Helper.h"

int main(int argc, char *argv[])
{
    uint8_t first = 0x11;
    uint8_t second = 0x22;

    uint16_t concated = Helper::ConcatTwoBytes(first, second);
    printf("Concated 0x%02X and 0x%02X: 0x%04X\n", first, second, concated);

    std::pair <uint8_t, uint8_t> bytes = Helper::DivideIntoTwoBytes(concated);
    uint8_t wasFirst = bytes.first;
    uint8_t wasSecond = bytes.second;
    printf("Divided 0x%04X into: 0x%02X and 0x%02X\n", concated, wasFirst, wasSecond);
}