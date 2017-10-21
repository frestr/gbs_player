#include <chrono>
#include <thread>
#include <iostream>
#include "apu.h"

APU::APU(SystemClock& clock)
    : frame_sequencer(256),
      power_on(true)
{
    // Prob. not what the APU sets these values to by default, but keep
    // them like this for the moment
    square1.set_volume(0);
    square2.set_volume(0);
    wave.enable_sound(false);
    wave.set_volume(0);
    noise.set_parameters(6, 1, 0);
    noise.set_volume(0);

    // Make the system clock clock the frame sequencer & all channels
    clock.add_timer(&frame_sequencer);
    clock.add_timer(&square1.get_timer());
    clock.add_timer(&square2.get_timer());
    clock.add_timer(&wave.get_timer());
    clock.add_timer(&noise.get_timer());
    clock.add_timer(&mixer.get_timer());

    // Make the frame sequencer clock all channels
    frame_sequencer.add_listener(&square1);
    frame_sequencer.add_listener(&square2);
    frame_sequencer.add_listener(&wave);
    frame_sequencer.add_listener(&noise);

    // Add all channels to the mixer
    mixer.add_channel(&square1);
    mixer.add_channel(&square2);
    mixer.add_channel(&wave);
    mixer.add_channel(&noise);
}

Mixer& APU::get_mixer()
{
    return mixer;
}

void APU::NR50_write(uint8_t value)
{
    uint8_t vin_left        = (value >> 7) & 1;
    uint8_t volume_left     = (value >> 4) & 7;
    uint8_t vin_right       = (value >> 3) & 1;
    uint8_t volume_right    = (value >> 0) & 7;

    // ignore vin settings

    mixer.set_master_volume(volume_left, volume_right);
}

void APU::NR51_write(uint8_t value)
{
    uint8_t noise_left      = (value >> 7) & 1;
    uint8_t wave_left       = (value >> 6) & 1;
    uint8_t square2_left    = (value >> 5) & 1;
    uint8_t square1_left    = (value >> 4) & 1;

    uint8_t noise_right     = (value >> 3) & 1;
    uint8_t wave_right      = (value >> 2) & 1;
    uint8_t square2_right   = (value >> 1) & 1;
    uint8_t square1_right   = (value >> 0) & 1;

    square1.enable_speakers(square1_left, square1_right);
    square2.enable_speakers(square2_left, square2_right);
    wave.enable_speakers(wave_left, wave_right);
    noise.enable_speakers(noise_left, noise_right);
}

void APU::NR52_write(uint8_t value)
{
    uint8_t power_on = value >> 7;
    if (! power_on) {
        // Set registers NR10-NR51 to 0

    }

    // Stop/start the frame sequencer & channel timers if the power is
    // turned on/off. Has no effect if the power state is unchanged
    frame_sequencer.set_running(power_on);
    square1.get_timer().set_running(power_on);
    square2.get_timer().set_running(power_on);
    wave.get_timer().set_running(power_on);
    noise.get_timer().set_running(power_on);

    this->power_on = power_on;

    uint8_t noise_on    = (value >> 3) & 1;
    uint8_t wave_on     = (value >> 2) & 1;
    uint8_t square2_on  = (value >> 1) & 1;
    uint8_t square1_on  = (value >> 0) & 1;

    // enable/disable particular channels
    noise.set_channel_enabled(noise_on);
    wave.set_channel_enabled(wave_on);
    square2.set_channel_enabled(square2_on);
    square1.set_channel_enabled(square1_on);
}

void APU::boot_sound()
{
    // Setup
    NR52_write(0x80);           // Turn APU power on
    square1.NRx1_write(0x80);   // Set duty cycle
    square1.NRx2_write(0xf3);   // Set full volume & period
    NR51_write(0xf3);           // Enable both left/right output for square channels
    NR50_write(0x77);           // Max master volume

    // Sound 1
    square1.NRx3_write(0x83);   // Set lower frequency
    square1.NRx4_write(0x87);   // Set upper frequency & trigger

    // Wait a little
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Sound 2
    square1.NRx3_write(0xc1);
    square1.NRx4_write(0x87);
}
