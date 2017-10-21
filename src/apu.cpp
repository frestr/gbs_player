#include <chrono>
#include <thread>
#include <iostream>
#include <cassert>
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

    regptr_table = {
        &Channel::NRx0_write,
        &Channel::NRx1_write,
        &Channel::NRx2_write,
        &Channel::NRx3_write,
        &Channel::NRx4_write,
    };
}

Mixer& APU::get_mixer()
{
    return mixer;
}

void APU::register_write(uint16_t addr, uint8_t value)
{
    assert(addr >= 0xFF10 && addr <= 0xFF3F);

    // No writes to registers when powered off
    if (! power_on && addr < 0xFF26)
        return;

    // Call the respective register write function of the respective channel
    uint8_t i = (addr - 0xFF10) % 5;
    if      (addr < 0xFF15) (dynamic_cast<Channel*>(&square1)->*regptr_table[i])(value);
    else if (addr < 0xFF1A) (dynamic_cast<Channel*>(&square2)->*regptr_table[i])(value);
    else if (addr < 0xFF1F) (dynamic_cast<Channel*>(&wave   )->*regptr_table[i])(value);
    else if (addr < 0xFF24) (dynamic_cast<Channel*>(&noise  )->*regptr_table[i])(value);
    else if (addr < 0xFF53) {
        if      (i == 0) NR50_write(value);
        else if (i == 1) NR51_write(value);
        else if (i == 2) NR52_write(value);
    } else if(addr >= 0xFF30 && addr <= 0xFF3F) {
        // set wave table value
    }
}

void register_read(uint16_t addr)
{

}

void APU::boot_sound()
{
    // Setup
    register_write(0xFF23, 0x80); // Turn APU power on
    register_write(0xFF11, 0x80); // Set duty cycle
    register_write(0xFF12, 0xF3); // Set full volume & period for square 1
    register_write(0xFF25, 0xF3); // Enable both left/right output for square channels
    register_write(0xFF24, 0x77); // Max master volume

    // Sound 1
    register_write(0xFF13, 0x83); // Set lower freq for square 1
    register_write(0xFF14, 0x87); // Set upper freq & trigger

    // Wait a little
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Sound 2
    register_write(0xFF13, 0xC1);
    register_write(0xFF14, 0x87);
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
        for (uint16_t a = 0xFF10; a < 0xFF26; ++a)
            register_write(a, 0);
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
