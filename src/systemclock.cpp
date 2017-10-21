#include "systemclock.h"
#include <ratio>
#include <thread>
#include <chrono>
#include <iostream>
#include "mixer.h"

SystemClock::SystemClock()
{

}

void SystemClock::start()
{
    const double period = 1000000000.0 / Mixer::SAMPLING_RATE;
    const int clocks_per_period = CLOCK_RATE / Mixer::SAMPLING_RATE;

    /*
     * This thread runs continually and clocks the whole system.
     * It is tied to the mixer's sampling rate, to make the mixer's
     * buffer fill up at approx. the same rate as the player can
     * play them. If the buffer fills up to fast, samples will need to be removed,
     * and this causes playback distortions between buffers.
     *
     * Note that no logic in the system is tied to real time (all timing except for
     * the player is done through this clock), and therefore
     * pausing like this will only affect the player (if it's pausing for too long).
     *
     * To make the system seem to run at approx. the correct speed, between each period
     * a set amount of clocks are done. This makes the system perform around
     * CLOCK_RATE clocks per second. Again, this has no effect on the internal logic.
     *
     */
    std::thread([&, period, clocks_per_period]() {
        while (true) {
            auto start = std::chrono::steady_clock::now();

            for (int i = 0; i < clocks_per_period+1; ++i)
                clock();

            while ((std::chrono::steady_clock::now() - start).count() < period);
        }
    }).detach();
}

// Can prob. implement this by just setting a flag (std::atomic<bool>)
// and then make the thread check that flag at each looop
/* void SystemClock::stop() */
/* { */

/* } */


void SystemClock::add_timer(Timer* timer)
{
    timers.push_back(timer);
}

void SystemClock::clock()
{
    for (auto& timer : timers)
        timer->clock();
}
