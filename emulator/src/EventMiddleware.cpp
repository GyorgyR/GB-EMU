//
// Created by gyorgy on 30/10/18.
//

#include "../include/EventMiddleware.h"

std::list<void (*)(int)> EventMiddleware::cpuCyclesSubscribers;
std::list<void (*)(int)> EventMiddleware::subscribersToDelete;

EventMiddleware::EventMiddleware() { }

EventMiddleware::~EventMiddleware() { }

void EventMiddleware::SubscribeToCpuCyclesPassed(void (*function)(int))
{
    cpuCyclesSubscribers.push_back(function);
}

void EventMiddleware::PublishCpuCyclesPassed(int cycles)
{
    //Delete subscribers that asked for deletion
    for (auto toDelete : subscribersToDelete) {
        cpuCyclesSubscribers.remove(toDelete);
    }

    //Empty deletion list
    subscribersToDelete = std::list<void (*)(int)>();

    //Call each subscriber method
    for (auto func : cpuCyclesSubscribers) {
        func(cycles);
    }
}

void EventMiddleware::UnsubscribeFromCpuCyclesPassed(void (*function)(int))
{
    subscribersToDelete.push_back(function);
}
