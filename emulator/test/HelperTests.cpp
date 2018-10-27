//
// Created by gyorgy on 07/10/18.
//
#include <cstdint>
#include <cstdio>

#include "../include/Helper.h"

void printBits(size_t const size, void const *const ptr)
{
    unsigned char *b = (unsigned char *) ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    printf("\t");
}

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

    uint8 allOnes = UINT8_MAX;
    printf("Start: ");
    printBits(sizeof(allOnes), &allOnes);
    Helper::ClearBit(&allOnes, 0);
    printf("Cleared bit 0: ");
    printBits(sizeof(allOnes), &allOnes);
    Helper::ClearBit(&allOnes, 7);
    printf("Cleared bit 7: ");
    printBits(sizeof(allOnes), &allOnes);
    Helper::ClearBit(&allOnes, 3);
    printf("Cleared bit 3: ");
    printBits(sizeof(allOnes), &allOnes);
    printf("\n");
}
