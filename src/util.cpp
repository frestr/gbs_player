#include "util.h"
#include <cassert>

uint64_t util::to_period(uint64_t freq)
{
    return SystemClock::CLOCK_RATE / freq;
}

uint64_t util::to_true_freq(uint16_t freq)
{
    assert(freq < 2048);
    return SystemClock::CLOCK_RATE / ((2048 - freq) << 5);
}
