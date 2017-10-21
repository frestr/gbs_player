#include "square2.h"
#include <stdexcept>
#include <cassert>
#include "systemclock.h"
#include <iostream>
#include "util.h"

Square2::Square2()
    : curr_phase(0),
      duty_cycle(2)
{
    set_frequency(1024);
}

void Square2::set_duty_cycle(uint8_t duty_cycle)
{
    if (duty_cycle > 3) {
        throw std::invalid_argument("duty_cycle must be in range [0, 3]");
        return;
    }
    this->duty_cycle = duty_cycle;
}

uint8_t Square2::get_duty_cycle()
{
    return duty_cycle;
}

void Square2::set_frequency(uint16_t freq)
{
    assert(freq < 2048);
    this->freq = freq;
    // multiply by 8, because each cycle takes 8 clocks
    set_timer_frequency(util::to_true_freq(freq) * 8);
}

uint16_t Square2::get_frequency()
{
    return freq;
}

uint8_t Square2::next_phase()
{
    uint8_t flip;
    switch (duty_cycle) {
        case 0:
            flip = 1; // 8 * 12.5 %
            break;
        case 1:
            flip = 2; // 8 * 25 %
            break;
        case 2:
            flip = 4; // 8 * 50 %
            break;
        case 3:
            flip = 6; // 8 * 75 %
            break;
        default:
            flip = 0;
    }
    // Note: 15 is the max value (we have a 4-bit DAC, so 2^4 - 1 = 15)
    uint8_t result = curr_phase < flip ? 15 : 0;
    // One phase cycle uses 8 clocks
    curr_phase = (curr_phase + 1) % 8;
    return result;
}
