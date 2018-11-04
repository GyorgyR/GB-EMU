//
// Created by gyorgy on 30/10/18.
//

#include "../include/DMA.h"
#include "../include/EventMiddleware.h"
#include "../include/MMU.h"

uint16 DMA::startAddress = 0;
uint16 DMA::currentDestAddress = 0;

DMA::DMA() { }

DMA::~DMA() { }

bool DMA::Start(uint8 address)
{
    //TODO: check if there is a transfer running ?
    startAddress = address * 0x100;
    currentDestAddress = destStartAddr;

    EventMiddleware::SubscribeToCpuCyclesPassed(DMA::Update);

    return true;
}

void DMA::Update(int cycles)
{
    for (int i = 0; i < cycles; i += 4) {
        uint8 value = MMU::ReadByteAt(startAddress++);
        MMU::WriteByteAt(currentDestAddress++, value);

        if (currentDestAddress > destinEndAddr) {
            EventMiddleware::UnsubscribeFromCpuCyclesPassed(DMA::Update);
            return;
        }
    }
}
