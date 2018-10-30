//
// Created by gyorgy on 30/10/18.
//

#include "../include/EventMiddleware.h"

std::list<void (*)(int)> EventMiddleware::cpuCyclesSubscribers;

EventMiddleware::EventMiddleware() { }

EventMiddleware::~EventMiddleware() { }

void EventMiddleware::SubscribeToCpuCyclesPassed(void (*function)(int))
{
    cpuCyclesSubscribers.push_back(function);
}

void EventMiddleware::PublishCpuCyclesPassed(int cycles)
{
    for (auto func : cpuCyclesSubscribers) {
        func(cycles);
    }
}

void EventMiddleware::UnsubscribeFromCpuCyclesPassed(void (*function)(int))
{
    cpuCyclesSubscribers.remove(function);
}
