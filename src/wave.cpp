#include "wave.h"
#include <cassert>
#include "systemclock.h"
#include "util.h"
#include <iostream>

Wave::Wave()
    : sample_index(0),
      curr_sample(0)
{
    // redefinitions from Channel
    length_counter_limit = 256;
    volume_limit = 4;

    samples.fill(0);
    set_frequency(1024); // Default?
}

double Wave::get_true_volume()
{
    if (! dac_enabled || ! channel_enabled)
        return 0.0;

    switch(volume) {
        case 0:
            return 0.0;
        case 1:
            return 1.0;
        case 2:
            return 0.5;
        case 3:
            return 0.25;
        // should not happen
        default:
            return 0.0;
    }
}

void Wave::trigger()
{
    sample_index = 0;
    Channel::trigger();
}

// set_frequency and get_frequency are very similar to the implementations
// in square2.cpp. maybe do this another way than defining two times?
void Wave::set_frequency(uint16_t freq)
{
    assert(freq < 2048);
    this->freq = freq;
    // multiply by 32, because each cycle takes 32 clocks
    set_timer_frequency(util::to_true_freq(freq) * 32);
}

uint16_t Wave::get_frequency()
{
    return freq;
}

void Wave::set_sample(uint8_t value, uint8_t index)
{
    assert(value < 16);
    assert(index < 32);
    samples[index] = value;
}

uint8_t Wave::get_sample(uint8_t index)
{
    assert(index < 32);
    return samples[index];
}

void Wave::NRx0_write(uint8_t value)
{
    dac_enabled = (value >> 7) & 1;
    if (! dac_enabled)
        channel_enabled = false;
}

void Wave::NRx1_write(uint8_t value)
{
    uint8_t length_load = value;
    set_length_counter(length_load);
}

void Wave::NRx2_write(uint8_t value)
{
    uint8_t volume = (value >> 5) & 3;
    set_volume(volume, false);
}

// NRx3 and NRx4 contain the same code as in square.cpp. DRY, so
// should prob. do this a better way, but making Channel implement
// only these two was a bit ugly
void Wave::NRx3_write(uint8_t value)
{
    uint8_t frequency_lower = value;
    uint16_t frequency = get_frequency();
    uint16_t new_freq = (frequency & 0xFF00) | frequency_lower;
    set_frequency(new_freq);
}

void Wave::NRx4_write(uint8_t value)
{
    uint8_t do_trigger = value >> 7;
    uint8_t length_enable = (value >> 6) & 1;
    enable_length_counter(length_enable);

    uint8_t frequency_upper = value & 0x7;
    uint16_t frequency = get_frequency();
    uint16_t new_freq = (frequency & 0xFF) | (frequency_upper << 8);
    set_frequency(new_freq);

    if (do_trigger)
        trigger();
}

uint8_t Wave::NRx0_read()
{
    return dac_enabled << 7;
}

uint8_t Wave::NRx1_read()
{
    return length_counter & 0xFF;
}

uint8_t Wave::NRx2_read()
{
    return (starting_volume << 5);
}

uint8_t Wave::NRx3_read()
{
    return freq & 0xFF;
}

uint8_t Wave::NRx4_read()
{
    return (length_counter_enabled << 6) | ((freq >> 8) & 7);
}

uint8_t Wave::next_phase()
{
    sample_index = (sample_index + 1) % 32;
    return samples[sample_index];    
}
