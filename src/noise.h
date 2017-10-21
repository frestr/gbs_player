#pragma once

#include "channel.h"

class Noise : public Channel
{
public:
    Noise();

    virtual void trigger();

    void set_parameters(uint8_t clock_shift, uint8_t width_mode, uint8_t divisor);
    uint8_t get_clock_shift();
    uint8_t get_width_mode();
    uint8_t get_divisor();

private:
    uint8_t clock_shift;
    uint8_t width_mode;
    uint8_t divisor;

    uint16_t shift_register;

    virtual uint8_t next_phase();
};
