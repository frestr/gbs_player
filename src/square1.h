#pragma once

#include "square2.h"
#include <cstdint>

// SquareCh1 is exactly like SquareCh2, except that it
// also can do frequency sweeps
class Square1 : public Square2
{
public:
    Square1(); 
    virtual void trigger();

    virtual void clock(Timer* timer);

    void set_sweep(uint8_t period, bool decrease, uint8_t shift);
    uint8_t get_sweep_period();
    bool is_sweep_decrease();
    uint8_t get_sweep_shift();

private:
    bool sweep_enabled;
    bool sweep_decrease;

    uint8_t sweep_period;
    uint8_t sweep_shift;
    uint64_t shadow_freq;

    uint8_t period_counter;

    void update_sweep(bool register_write = true);
};
