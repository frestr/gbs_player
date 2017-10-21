#pragma once

#include <cstdint>
#include "timer.h"

class Channel : public TimerListener
{
public:
    Channel();

    // Returns the most recently clocked sample value
    // NOTE: the returned value is 4 bit. Only the lower 4 bits
    // are used, the upper 4 bits will be 0
    uint8_t get_sample();

    virtual void clock(Timer* timer);

    Timer& get_timer();

    // this sets the actual sound frequency in Hz
    // (not the value that is written to the register)
    void set_timer_frequency(uint64_t frequency);

    // volume is in range [0, 15] (0 is off, 15 is loudest)
    void set_volume(uint8_t volume);
    uint8_t get_volume();
    virtual double get_true_volume();

    void set_length_counter(uint16_t length_counter);
    uint16_t get_length_counter();
    void enable_length_counter(bool enabled);
    bool is_length_counter_enabled();

    void set_frame_sequencer(Timer* frame_sequencer);

    // envelope is enabled on trigger
    void set_envelope(uint8_t period, bool add);
    uint8_t get_envelope_period();
    bool is_envelope_add();

    // this can be overridden in any child classes,
    // but make sure they also call the base class version
    virtual void trigger();

protected:
    bool channel_enabled;
    uint16_t length_counter; // [0, 256] for wave, [0, 64] for rest
    uint16_t length_counter_limit; // 256 for wave, 64 for rest
    bool length_counter_enabled;
    Timer timer;

    uint8_t volume; // 4-bit, the current volume
    uint8_t volume_limit;
    // the volume the channel was set to via set_volume
    // (volume may be changed internally, but starting_volume will stay the same)
    uint8_t starting_volume; 

    uint64_t frame_sequencer_ticks;

    void update_envelope();

private:
    uint8_t curr_sample; // 4-bit

    uint8_t envelope_period;
    uint8_t envelope_period_counter;
    bool envelope_add;

    Timer* frame_sequencer;

    virtual uint8_t next_phase() = 0;
};
