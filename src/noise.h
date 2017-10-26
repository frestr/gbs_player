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

    virtual void NRx0_write(uint8_t value);
    virtual void NRx1_write(uint8_t value);
    virtual void NRx2_write(uint8_t value);
    virtual void NRx3_write(uint8_t value);
    virtual void NRx4_write(uint8_t value);

    virtual uint8_t NRx0_read();
    virtual uint8_t NRx1_read();
    virtual uint8_t NRx2_read();
    virtual uint8_t NRx3_read();
    virtual uint8_t NRx4_read();

private:
    uint8_t clock_shift;
    uint8_t width_mode;
    uint8_t divisor;

    uint16_t shift_register;

    virtual uint8_t next_phase();
};
