//
// Created by gyorgy on 28/10/18.
//

#include <iostream>
#include <cstdint>
#include <chrono>
#include <thread>

#include "../include/Window.h"
#include "../include/Joypad.h"

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

int main()
{
    Window window;

    std::cout << "\e[?25l";
    std::flush(std::cout);

    uint8_t returned = 0;

    uint8_t readDir = 0b00100000;
    uint8_t readBut = 0b00010000;

    Joypad::WriteToRegister(readDir);
    while (returned != 0b11100000) {
        returned = Joypad::ReadRegister();
        std::cout << "\rReturned: ";
        printBits(sizeof(returned), &returned);
    }
    std::cout << std::endl;

    Joypad::WriteToRegister(readBut);
    while (returned != 0b11010000) {
        returned = Joypad::ReadRegister();
        std::cout << "\rReturned: ";
        printBits(sizeof(returned), &returned);
    }
    std::cout << std::endl;


    std::cout << "\e[?25h";
    std::flush(std::cout);
}