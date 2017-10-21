#pragma once

#include "square1.h"
#include "square2.h"
#include "wave.h"
#include "noise.h"
#include "timer.h"
#include "systemclock.h"
#include "mixer.h"

// Audio Processing Unit
class APU
{
public:
    APU(SystemClock& clock);

    Mixer& get_mixer();

    void boot_sound();

private:
    Square1 square1;
    Square2 square2;
    Wave wave;
    Noise noise;

    Timer frame_sequencer;
    Mixer mixer;

    bool power_on;

    void NR50_write(uint8_t value);
    void NR51_write(uint8_t value);
    void NR52_write(uint8_t value);
};
