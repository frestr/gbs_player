#include "square1.h"
#include <cassert>
#include <iostream>

Square1::Square1()
{
    set_sweep(0, true, 0);
}

void Square1::trigger()
{
    Square2::trigger();

    shadow_freq = freq;
    period_counter = sweep_period;
    sweep_enabled = (sweep_period > 0 && sweep_shift > 0);

    if (sweep_enabled)
        update_sweep(false);
}

void Square1::clock(Timer* timer)
{
    Square2::clock(timer);
    uint64_t freq = timer->get_frequency();
    // The Channel base class updates frame_sequencer_ticks, but we
    // need to check ourselves if the frame sequencer did the clock
    if (timer != &(this->timer) && freq == 256) {
        // sweep clock is 128 hz
        if (frame_sequencer_ticks % 2 == 0) {
            if (channel_enabled && sweep_enabled) {
                if (period_counter == 1) {
                    update_sweep();
                    period_counter = sweep_period;
                }
                if (period_counter > 1)
                    --period_counter;
            }
        }
    }
}

void Square1::set_sweep(uint8_t period, bool decrease, uint8_t shift)
{
    assert(period < 8);
    assert(shift < 8);

    sweep_period = period;
    period_counter = sweep_period;
    sweep_decrease = decrease;
    sweep_shift = shift;
}

uint8_t Square1::get_sweep_period()
{
    return sweep_period;
}

bool Square1::is_sweep_decrease()
{
    return sweep_decrease;
}

uint8_t Square1::get_sweep_shift()
{
    return sweep_shift;
}

void Square1::NRx0_write(uint8_t value)
{
    uint8_t sweep_period   = (value >> 4) & 7;
    uint8_t sweep_decrease = (value >> 3) & 1;
    uint8_t sweep_shift    = (value >> 0) & 7;
    set_sweep(sweep_period, sweep_decrease, sweep_shift);
}

uint8_t Square1::NRx0_read()
{
    return (sweep_period << 4) | (sweep_decrease << 3) | sweep_shift;
}

void Square1::update_sweep(bool register_write)
{
    // Note: if set to decrease, the freq will converge to a low value, but
    // unlike the overflow check which disables the channel when the frequency
    // becomes too high, this low value is kept constant and the channel is not disabled
    // (resulting in a constant, low freq sound)
    uint64_t new_freq = shadow_freq + (shadow_freq >> sweep_shift) * (sweep_decrease ? -1 : 1);
    if (new_freq < 2048) {
        if (register_write) {
            shadow_freq = new_freq;
            set_frequency(shadow_freq);
            // Do the calculation once more (from the spec)
            // this is to make sure the channel is disabled if the next
            // call will disable it anyway
            update_sweep(false);
        }
    } else {
        channel_enabled = false;        
    }
}
