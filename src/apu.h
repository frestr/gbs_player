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
private:
    Square1 square1;
    Square2 square2;
    Wave wave;
    Noise noise;

    Timer frame_sequencer;
    Mixer mixer;
};
