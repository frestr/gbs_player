#pragma once

#include "channel.h"
#include <cstdint>

class Square2 : public Channel
{
public:
    Square2();

    void set_duty_cycle(uint8_t duty_cycle);
    uint8_t get_duty_cycle();

    void set_frequency(uint16_t freq);
    uint16_t get_frequency();

protected:
    uint16_t freq;

private:
    uint8_t curr_phase;

    // can be 0 (12.5%), 1 (25%), 2 (50%), or 3 (75%)
    uint8_t duty_cycle;

    virtual uint8_t next_phase();
};
