#include "systemclock.h"
#include <ratio>
#include <thread>
#include <chrono>
#include <iostream>
#include "mixer.h"

SystemClock::SystemClock()
{

}

void SystemClock::add_timer(Timer* timer)
{
    timers.push_back(timer);
}

void SystemClock::clock()
{
    for (auto& timer : timers)
        timer->clock();
}
