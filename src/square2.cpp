#include <stdexcept>
#include <cassert>
#include <iostream>
#include "square2.h"
#include "systemclock.h"
#include "util.h"

Square2::Square2()
    : curr_phase(0),
      duty_cycle(2)
{
    set_frequency(1024);
}

void Square2::set_duty_cycle(uint8_t duty_cycle)
{
    assert(duty_cycle < 4);
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

void Square2::NRx0_write(uint8_t value)
{
    // Not used
}

void Square2::NRx1_write(uint8_t value)
{
    uint8_t duty = value >> 6;
    uint8_t length = value & 0x3f;
    set_duty_cycle(duty);
    set_length_counter(length);
}

void Square2::NRx2_write(uint8_t value)
{
    uint8_t volume = value >> 4;
    uint8_t envelope_mode = (value >> 3) & 1;
    uint8_t envelope_period = value & 0x7;
    set_volume(volume);
    set_envelope(envelope_period, envelope_mode);
}

void Square2::NRx3_write(uint8_t value)
{
    uint8_t frequency_lower = value;
    uint16_t frequency = get_frequency();
    uint16_t new_freq = (frequency & 0xff00) | frequency_lower;
    set_frequency(new_freq);
}

void Square2::NRx4_write(uint8_t value)
{
    uint8_t do_trigger = value >> 7;
    uint8_t length_enable = (value >> 6) & 1;
    enable_length_counter(length_enable);

    uint8_t frequency_upper = value & 0x7;
    uint16_t frequency = get_frequency();
    uint16_t new_freq = (frequency & 0xff) | (frequency_upper << 8);
    set_frequency(new_freq);

    if (do_trigger == 1)
        trigger();
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
    // One waveform cycle uses 8 clocks
    curr_phase = (curr_phase + 1) % 8;
    return result;
}
