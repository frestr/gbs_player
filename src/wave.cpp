#include "wave.h"
#include <cassert>
#include "systemclock.h"
#include "util.h"
#include <iostream>

Wave::Wave()
    : sample_index(0),
      sound_enabled(true)
{
    // redefinitions from Channel
    length_counter_limit = 256;
    volume_limit = 4;

    set_length_counter(length_counter_limit - 1);
    samples.fill(0);
}

void Wave::enable_sound(bool enable)
{
    sound_enabled = enable;    
}

double Wave::get_true_volume()
{
    if (!sound_enabled || !channel_enabled)
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
    Channel::trigger();
    sample_index = 0;
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

void Wave::set_samples(std::array<uint8_t, 32> samples)
{
    this->samples = samples;
}

std::array<uint8_t, 32> Wave::get_samples()
{
    return samples;
}

void Wave::NRx0_write(uint8_t value)
{

}

void Wave::NRx1_write(uint8_t value)
{

}

void Wave::NRx2_write(uint8_t value)
{

}

void Wave::NRx3_write(uint8_t value)
{

}

void Wave::NRx4_write(uint8_t value)
{

}

uint8_t Wave::next_phase()
{
    sample_index = (sample_index + 1) % 32;
    return samples[sample_index];    
}
