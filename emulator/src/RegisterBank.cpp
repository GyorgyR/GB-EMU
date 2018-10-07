//
// Created by gyorgy on 17/09/18.
//
#include <cstdio>

#include "../include/RegisterBank.h"
#include "../include/Helper.h"

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

bool RegisterBank::IsZSet()
{
    return 0b10000000 & F;
}

bool RegisterBank::IsNSet() {
    return 0b01000000 & F;
}

bool RegisterBank::IsHSet() {
    return 0b00100000 & F;
}

bool RegisterBank::IsCSet()
{
    return 0b00010000 & F;
}

uint16_t RegisterBank::AF()
{
    return Helper::ConcatTwoBytes(A, F);
}

uint16_t RegisterBank::BC()
{
    return Helper::ConcatTwoBytes(B, C);
}

uint16_t RegisterBank::DE()
{
    return Helper::ConcatTwoBytes(D, E);
}

uint16_t RegisterBank::HL()
{
    return Helper::ConcatTwoBytes(H, L);
}

void RegisterBank::AF(uint16_t value) {
    std::pair<uint8_t, uint8_t> bytes = Helper::DivideIntoTwoBytes(value);
    A = bytes.first;
    F = bytes.second;
}

void RegisterBank::BC(uint16_t value) {
    std::pair<uint8_t, uint8_t> bytes = Helper::DivideIntoTwoBytes(value);
    B = bytes.first;
    C = bytes.second;
}

void RegisterBank::DE(uint16_t value) {
    std::pair<uint8_t, uint8_t> bytes = Helper::DivideIntoTwoBytes(value);
    D = bytes.first;
    E = bytes.second;
}

void RegisterBank::HL(uint16_t value) {
    std::pair<uint8_t, uint8_t> bytes = Helper::DivideIntoTwoBytes(value);
    H = bytes.first;
    L = bytes.second;
}

void RegisterBank::SetZ(bool isOn) {
    if (isOn) RegisterBank::F |= 0b10000000;
    else RegisterBank::F &= 0b01111111;
}

void RegisterBank::SetC(bool isOn) {
    if (isOn) RegisterBank::F |= 0b00010000;
    else RegisterBank::F &= 0b11101111;
}

void RegisterBank::SetN(bool isOn) {
    if (isOn) RegisterBank::F |= 0b01000000;
    else RegisterBank::F &= 0b10111111;
}

void RegisterBank::SetH(bool isOn) {
    if (isOn) RegisterBank::F |= 0b00100000;
    else RegisterBank::F &= 0b11011111;
}
