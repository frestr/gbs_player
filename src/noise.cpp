#include "noise.h"
#include <cassert>
#include "systemclock.h"
#include <iostream>

Noise::Noise()
    : clock_shift(0),
      width_mode(false),
      divisor(0),
      shift_register(0xFFFF)
{

}

void Noise::trigger()
{
    Channel::trigger();
    shift_register = 0xFFFF;
}

void Noise::set_parameters(uint8_t clock_shift, uint8_t width_mode, uint8_t divisor)
{
    assert(clock_shift < 14);
    assert(width_mode < 2);
    assert(divisor < 8);
    this->clock_shift = clock_shift;
    this->width_mode = width_mode;
    this->divisor = divisor;    

    set_timer_frequency((1048576 / (divisor + 1 )) >> (clock_shift + 1));
}

uint8_t Noise::get_clock_shift()
{
    return clock_shift;
}

uint8_t Noise::get_width_mode()
{
    return width_mode;
}

uint8_t Noise::get_divisor()
{
    return divisor;
}

void Noise::NRx0_write(uint8_t value)
{
    // not used
}

void Noise::NRx1_write(uint8_t value)
{
    uint8_t length_load = value & 0x3F; 
    set_length_counter(length_load);
}

// Same as in Square2
void Noise::NRx2_write(uint8_t value)
{
    uint8_t volume = value >> 4;
    uint8_t envelope_mode = (value >> 3) & 1;
    uint8_t envelope_period = value & 0x7;
    set_volume(volume);
    set_envelope(envelope_period, envelope_mode);
}

void Noise::NRx3_write(uint8_t value)
{
    uint8_t clock_shift = (value >> 4) & 0xF;
    uint8_t width_mode = (value >> 3) & 1;
    uint8_t divisor_code = value & 7;
    set_parameters(clock_shift, width_mode, divisor_code);
}

void Noise::NRx4_write(uint8_t value)
{
    uint8_t do_trigger = value >> 7;
    uint8_t length_enable = (value >> 6) & 1;
    enable_length_counter(length_enable);

    if (do_trigger)
        trigger();
}

// Note: compared to VBA-M, the noise sounds a bit harsh. This may be because
// VBA-M does some kind of high-pass filter
uint8_t Noise::next_phase()
{
    // Simple LFSR implementation
    uint16_t bit = ((shift_register >> 0) ^ (shift_register >> 1)) & 1;
    shift_register >>= 1;
    if (width_mode == 1) {
        // Because shift_register is 16-bit, we need to manually clear the
        // 7th bit before setting it (it's not cleared by the shift like the 15th bit)
        /* shift_register &= 0x3f; // Do we need this? it seems to have no affect */
        shift_register |= (bit << 6);
    } else {
        // 15-bit LFSR
        shift_register |= (bit << 14);
    }

    // Return last bit inverted, and multiply by 15 to get max volume
    return ((~shift_register) & 1) * 15;
}
