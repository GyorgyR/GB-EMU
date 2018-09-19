//
// Created by gyorgy on 17/09/18.
//

#include "../include/RegisterBank.h"
const uint16_t bit_mask = 0b0000000011111111;

uint8_t RegisterBank::A = 0;
uint8_t RegisterBank::B = 0;
uint8_t RegisterBank::C = 0;
uint8_t RegisterBank::D = 0;
uint8_t RegisterBank::E = 0;
uint8_t RegisterBank::F = 0;
uint8_t RegisterBank::H = 0;
uint8_t RegisterBank::L = 0;

uint16_t RegisterBank::SP = 0;
uint16_t RegisterBank::PC = 0;

bool RegisterBank::IsZero()
{
    return 0b10000000 & F;
}

bool RegisterBank::IsCarry()
{
    return 0b00010000 & F;
}

uint16_t RegisterBank::AF()
{
    return (A << 8) + F;
}

uint16_t RegisterBank::BC()
{
    return (B << 8) + C;
}

uint16_t RegisterBank::DE()
{
    return (D << 8) + E;
}

uint16_t RegisterBank::HL()
{
    return (H << 8) + L;
}

void RegisterBank::AF(uint16_t value) {
    F = value & bit_mask;
    A = (value >> 8) & bit_mask;
}

void RegisterBank::BC(uint16_t value) {
    C = value & bit_mask;
    B = (value >> 8) & bit_mask;
}

void RegisterBank::DE(uint16_t value) {
    E = value & bit_mask;
    D = (value >> 8) & bit_mask;
}

void RegisterBank::HL(uint16_t value) {
    L = value & bit_mask;
    H = (value >> 8) & bit_mask;
}
