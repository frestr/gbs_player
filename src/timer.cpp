#include "timer.h"
#include "channel.h"
#include "systemclock.h"
#include <iostream>

Timer::Timer(uint64_t frequency)
    : running(true)
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
    if (! running)
        return;

    // To prevent integer underflow
    if (counter > 0)
        --counter;
    if (counter <= 0) {
        counter = period;
        for (auto& listener : listeners)
            listener->clock(this);
    }    
}

void Timer::set_running(bool running)
{
    this->running = running;
    if (! running)
        counter = period;
}

bool Timer::is_first_half()
{
    return counter >= period/2;
}
