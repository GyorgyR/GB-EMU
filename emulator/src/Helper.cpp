//
// Created by gyorgy on 19/09/18.
//

#define DEBUG

#include <cstdio>

#include "../include/Helper.h"

ofstream Helper::debugLog;
ofstream Helper::ramLog;
ofstream Helper::cpuLog;

uint16_t Helper::ConcatTwoBytes(uint8_t first, uint8_t second) {
    return (first << 8) + second;
}

std::pair<uint8_t, uint8_t> Helper::DivideIntoTwoBytes(uint16_t value) {
    const uint16_t bit_mask = 0b0000000011111111;
    return std::make_pair(value & bit_mask, (value >> 8) & bit_mask);
}

Helper::Helper()
{

}

Helper::~Helper()
{

}

void Helper::InitLogger()
{
    #ifdef DEBUG
    debugLog.open("logs/debug.log", std::ios::out | std::ios::trunc);
    ramLog.open("logs/ram.debug.log", std::ios::out | std::ios::trunc);
    cpuLog.open("logs/cpu.debug.log", std::ios::out | std::ios::trunc);
    #else
    return
    #endif
}

void Helper::Log(const std::string message)
{
    #ifdef DEBUG
    debugLog << message << std::endl;
    debugLog.flush();
    #else
    return;
    #endif
}

void Helper::CPULog(const std::string message)
{
    #ifdef DEBUG
    cpuLog << message << std::endl;
    cpuLog.flush();
    #else
    return;
    #endif
}

void Helper::RAMLog(const std::string message)
{
    #ifdef DEBUG
    ramLog << message << std::endl;
    ramLog.flush();
    #else
    return
    #endif
}
