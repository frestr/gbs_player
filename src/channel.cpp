#include "channel.h"
#include "util.h"
#include <iostream>
#include <chrono>
#include <cassert>

Channel::Channel()
    : channel_enabled(true),
      length_counter_limit(64),
      length_counter_enabled(false),
      volume_limit(16),
      frame_sequencer_ticks(0),
      envelope_period(0),
      envelope_add(false),
      dac_enabled(true),
      length_newly_enabled(false),
      curr_sample(0),
      envelope_period_counter(0),
      left_speaker_enabled(false),
      right_speaker_enabled(false)
{
    timer.add_listener(this);
    set_volume(volume_limit - 1);
    set_timer_frequency(0);
    set_length_counter(0);
}

uint8_t Channel::get_sample()
{
    return curr_sample;
}

void Channel::clock(Timer* timer)
{
    if (! dac_enabled)
        channel_enabled = false;

    if (timer == &(this->timer)) {
        curr_sample = next_phase();
    } else {
        uint64_t freq = timer->get_frequency();
        // If the frequency is 256, we assume it's the frame sequencer.
        // Not the best way to check, may need to be fixed later
        if (freq == 256) {
            ++frame_sequencer_ticks;
            // update length counter
            if (length_counter_enabled && length_counter > 0) {
                --length_counter;
                if (length_counter <= 0)
                    channel_enabled = false;
            }
            // the envelope is updated at 64 Hz, so run this every fourth time
            // the frame sequencer clocks (hence the modulo)
            if (frame_sequencer_ticks % 4 == 0) {
                update_envelope();
            }
        }
    }
}

Timer& Channel::get_timer()
{
    return timer;
}

void Channel::set_timer_frequency(uint64_t frequency)
{
    timer.set_frequency(frequency);
}

void Channel::set_volume(uint8_t volume, bool set_dac_enabled)
{
    assert(volume < volume_limit);
    this->volume = volume;
    starting_volume = volume;

    if (set_dac_enabled) {
        if (volume == 0 && ! envelope_add) {
            dac_enabled = false;
            channel_enabled = false;
        } else {
            dac_enabled = true;
        }
    }
}

uint8_t Channel::get_volume()
{
    return volume;
}

double Channel::get_true_volume()
{
    if (! channel_enabled || ! dac_enabled)
        return 0.0;
    return volume / 15.0;
}

void Channel::set_length_counter(uint16_t length_counter)
{
    assert(length_counter <= length_counter_limit);
    this->length_counter = length_counter_limit - length_counter;
    /* std::cout << ">> Len set: " << (unsigned int)(this->length_counter) << "\n"; */
}

uint16_t Channel::get_length_counter()
{
    return length_counter;
}

void Channel::enable_length_counter(bool enabled)
{
    bool newly_enabled = (! length_counter_enabled && enabled);
    length_counter_enabled = enabled;

    length_newly_enabled = newly_enabled;

/*     /1* std::cout << "PRE " << length_counter << "\n"; *1/ */

    // Clock length counter if length counter goes from disabled to enabled
    // and is in first half of frame sequencer period
    if (length_counter > 0
            && newly_enabled
            && frame_sequencer != NULL
            && frame_sequencer->is_first_half())
        clock(frame_sequencer);

    /* std::cout << "POST " << length_counter << "\n"; */
}

bool Channel::is_length_counter_enabled()
{
    return length_counter_enabled;
}

void Channel::set_channel_enabled(bool enabled)
{
    channel_enabled = enabled;
}

bool Channel::is_channel_enabled()
{
    return channel_enabled;
}

void Channel::set_frame_sequencer(Timer* frame_sequencer)
{
    this->frame_sequencer = frame_sequencer;
    frame_sequencer->add_listener(this);
}

void Channel::set_envelope(uint8_t period, bool add)
{
    assert(period < 8);

    envelope_period = period;
    envelope_period_counter = 0; // the envelope itself begins on trigger
    envelope_add = add;

    if (volume == 0 && ! envelope_add) {
        dac_enabled = false;
        channel_enabled = false;
    } else {
        dac_enabled = true;
    }
}

uint8_t Channel::get_envelope_period()
{
    return envelope_period;
}

bool Channel::is_envelope_add()
{
    return envelope_add;
}

void Channel::enable_speakers(bool left, bool right)
{
    left_speaker_enabled = left;
    right_speaker_enabled = right;
}

bool Channel::is_left_speaker_enabled()
{
    return left_speaker_enabled;
}

bool Channel::is_right_speaker_enabled()
{
    return right_speaker_enabled;
}

void Channel::trigger()
{
    if (length_counter == 0) {
        set_length_counter(0);
        // Clock if length counter enabled
        if (length_newly_enabled && frame_sequencer != NULL) {
            clock(frame_sequencer);
        }
    }
    envelope_period_counter = envelope_period;
    set_volume(starting_volume, false);
    if (! dac_enabled)
        channel_enabled = false;
}

void Channel::update_envelope()
{
    // Check if it would become 0 if we decremented it now, but don't
    // do it as we want value 0 to mean disabled
    if (envelope_period_counter == 1) {
        if (volume > 0 && !envelope_add)
            --volume;
        else if (volume < 15 && envelope_add)
            ++volume;
        envelope_period_counter = envelope_period;
    } else if (envelope_period_counter != 0) {
        --envelope_period_counter;
    }
}
