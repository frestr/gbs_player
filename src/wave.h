#pragma once

#include "channel.h"
#include <array>

class Wave : public Channel
{
public:
    Wave();

    // hide the update_envelope function from Channel, since
    // there's no envelope for wave
    void update_envelope() {};

    virtual double get_true_volume();

    virtual void trigger();

    void set_frequency(uint16_t frequency);
    uint16_t get_frequency();

    void set_sample(uint8_t value, uint8_t index);
    uint8_t get_sample(uint8_t index);

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
    uint16_t freq;
    std::array<uint8_t, 32> samples;
    uint8_t sample_index;
    uint8_t curr_sample;

    virtual uint8_t next_phase();
};
