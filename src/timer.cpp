#include "timer.h"
#include "channel.h"
#include "systemclock.h"
#include <iostream>

Timer::Timer(uint64_t frequency)
{
    set_frequency(frequency);
}

void Timer::set_frequency(uint64_t frequency)
{
    this->frequency = frequency;
    period = 0;
    if (frequency > 0)
        period = SystemClock::CLOCK_RATE / frequency;
    counter = period;
}

uint64_t Timer::get_frequency()
{
    return frequency;
}

void Timer::add_listener(TimerListener* listener)
{
    listeners.push_back(listener);
}

void Timer::clock()
{
    // To prevent integer underflow
    if (counter > 0)
        --counter;
    if (counter <= 0) {
        counter = period;
        for (auto& listener : listeners)
            listener->clock(this);
    }    
}
