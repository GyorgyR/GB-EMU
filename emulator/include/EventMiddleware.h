//
// Created by gyorgy on 30/10/18.
//

#ifndef GB_EMULATOR_EVENTMIDDLEWARE_H
#define GB_EMULATOR_EVENTMIDDLEWARE_H

#include <list>

class EventMiddleware
{
private:
    //Make class static
    EventMiddleware();
    ~EventMiddleware();

    static std::list<void (*)(int)> cpuCyclesSubscribers;
    static std::list<void (*)(int)> subscribersToDelete;
public:
    static void PublishCpuCyclesPassed(int cycles);
    static void SubscribeToCpuCyclesPassed(void function(int));
    static void UnsubscribeFromCpuCyclesPassed(void function(int));
};


#endif //GB_EMULATOR_EVENTMIDDLEWARE_H
