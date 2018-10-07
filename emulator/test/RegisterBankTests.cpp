//
// Created by gyorgy on 07/10/18.
//

#include <cstdint>
#include <cstdio>

#include "../include/RegisterBank.h"

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

void printWhatIsSet()
{
    printf("Z: %s,\t", RegisterBank::IsZSet() ? "true" : "false");
    printf("N: %s,\t", RegisterBank::IsNSet() ? "true" : "false");
    printf("H: %s,\t", RegisterBank::IsHSet() ? "true" : "false");
    printf("C: %s,\t", RegisterBank::IsCSet() ? "true" : "false");
}

void printF()
{
    printBits(sizeof(RegisterBank::F), &RegisterBank::F);
    printWhatIsSet();
    puts("");
}

int main(int argc, char *argv[])
{
    printf("  WAS F: ");
    printF();

    printf("  Set Z: ");
    RegisterBank::SetZ(true);
    printF();

    printf("  Set N: ");
    RegisterBank::SetN(true);
    printF();

    printf("  Set H: ");
    RegisterBank::SetH(true);
    printF();

    printf("  Set C: ");
    RegisterBank::SetC(true);
    printF();

    printf("Unset C: ");
    RegisterBank::SetC(false);
    printF();

    printf("Unset H: ");
    RegisterBank::SetH(false);
    printF();

    printf("Unset N: ");
    RegisterBank::SetN(false);
    printF();

    printf("Unset Z: ");
    RegisterBank::SetZ(false);
    printF();
}