//
// Created by gyorgy on 17/09/18.
//
#include <cstdio>

#include "../include/RegisterBank.h"
#include "../include/Helper.h"

uint8 RegisterBank::A = 0x01;
uint8 RegisterBank::B = 0;
uint8 RegisterBank::C = 0x13;
uint8 RegisterBank::D = 0;
uint8 RegisterBank::E = 0xD8;
uint8 RegisterBank::F = 0xB0;
uint8 RegisterBank::H = 0x01;
uint8 RegisterBank::L = 0x4D;
uint16 RegisterBank::SP = 0xFFFE;

uint16 RegisterBank::PC = 0;

uint8 RegisterBank::interruptFlag = 0;
uint8 RegisterBank::interruptEnable = 0;
bool RegisterBank::areInterruptsEnabled = false;

bool RegisterBank::IsZSet()
{
    return Helper::IsBitSet(F, 7);
}

bool RegisterBank::IsNSet() {
    return Helper::IsBitSet(F, 6);
}

bool RegisterBank::IsHSet() {
    return Helper::IsBitSet(F, 5);
}

bool RegisterBank::IsCSet()
{
    return Helper::IsBitSet(F, 4);
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

RegisterBank::RegisterBank() {

}

RegisterBank::~RegisterBank() {

}

bool RegisterBank::AreInterruptsEnabled() {
    return areInterruptsEnabled;
}

void RegisterBank::SetInterruptEnabled(bool enabled) {
    areInterruptsEnabled = enabled;
}

uint8 RegisterBank::InterruptFlag() {
    return interruptFlag;
}

void RegisterBank::InterruptFlag(uint8 value) {
    interruptFlag = value;
}

uint8 RegisterBank::InterruptEnable() {
    return interruptEnable;
}

void RegisterBank::InterruptEnable(uint8 value) {
    interruptEnable = value;
}

void RegisterBank::SetBitInIF(int bit)
{
    Helper::SetBit(&interruptFlag, bit);
}

void RegisterBank::ClearBitInIF(int bit)
{
    Helper::ClearBit(&interruptFlag, bit);
}
