//
// Created by gyorgy on 19/09/18.
//

#include <cstdio>

#include "../include/Helper.h"

uint16_t Helper::ConcatTwoBytes(uint8_t first, uint8_t second) {
    return (second << 8) + first;
}

std::pair<uint8_t, uint8_t> Helper::DivideIntoTwoBytes(uint16_t value) {
    const uint16_t bit_mask = 0b0000000011111111;
    return std::make_pair(value & bit_mask, (value >> 8) & bit_mask);
}
