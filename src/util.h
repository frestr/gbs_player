#pragma once

#include "systemclock.h"

namespace util
{
    // freq must be in Hz. result will be in clock cycles
    uint64_t to_period(uint64_t freq);

    // convert raw (register) frequency to true (audible) frequency
    uint64_t to_true_freq(uint16_t freq);
}
