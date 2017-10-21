#pragma once

#include "timer_listener.h"
#include <vector>
#include <cstdint>

class Channel;

class Timer
{
public:
    Timer(uint64_t frequency = 0);

    void set_frequency(uint64_t frequency);
    uint64_t get_frequency();

    void add_listener(TimerListener* listener);

    void clock();

private:
    uint64_t frequency;
    uint64_t period; // in clock cycles
    uint64_t counter; // down-counter
    
    std::vector<TimerListener*> listeners;
};
