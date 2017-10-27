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

    void register_write(uint16_t addr, uint8_t value);
    uint8_t register_read(uint16_t addr);

    void reset();

    // This should not really be in APU itself, but rather some
    // external test class. Defined in apu_test.cpp
    void run_tests();

private:
    Square1 square1;
    Square2 square2;
    Wave wave;
    Noise noise;

    Timer frame_sequencer;
    Mixer mixer;

    bool power_on;

    uint8_t vin_left;
    uint8_t vin_right;

    typedef void (Channel::*RegWrite)(uint8_t);
    std::array<RegWrite, 5> regwrite_ptr;

    typedef uint8_t (Channel::*RegRead)();
    std::array<RegRead, 5> regread_ptr;

    std::array<std::array<uint8_t, 5>, 5> register_mask;

    void NR50_write(uint8_t value);
    void NR51_write(uint8_t value);
    void NR52_write(uint8_t value);

    uint8_t NR50_read();
    uint8_t NR51_read();
    uint8_t NR52_read();
};
