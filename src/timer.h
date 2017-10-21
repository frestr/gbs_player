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

    // Note: the clock method will still be called by the system clock.
    // This method just decides whether the clock should be ignored or
    // not. It's not necessary to start the timer if it was not
    // previously stopped.
    void set_running(bool running);

private:
    uint64_t frequency;
    uint64_t period; // in clock cycles
    uint64_t counter; // down-counter
    bool running;
    
    std::vector<TimerListener*> listeners;
};
