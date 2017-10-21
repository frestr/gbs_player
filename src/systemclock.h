#pragma once

#include <vector>
#include "timer.h"

class SystemClock
{
public:
    static const uint64_t CLOCK_RATE = 4194304;
    
    SystemClock();

    void start();
    /* void stop(); */

    void add_timer(Timer* timer);

    void clock();

private:
    // not copyable
    SystemClock(const SystemClock&);
    SystemClock& operator = (const SystemClock&);

    std::vector<Timer*> timers;
};
