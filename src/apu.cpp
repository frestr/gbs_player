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

    regwrite_ptr = {
        &Channel::NRx0_write,
        &Channel::NRx1_write,
        &Channel::NRx2_write,
        &Channel::NRx3_write,
        &Channel::NRx4_write,
    };

    regread_ptr = {
        &Channel::NRx0_read,
        &Channel::NRx1_read,
        &Channel::NRx2_read,
        &Channel::NRx3_read,
        &Channel::NRx4_read,
    };

    register_mask = {{
        {0x80, 0x3F, 0x00, 0xFF, 0xBF},
        {0xFF, 0x3F, 0x00, 0xFF, 0xBF},
        {0x7F, 0xFF, 0x9F, 0xFF, 0xBF},
        {0xFF, 0xFF, 0x00, 0x00, 0xBF},
        {0x00, 0x00, 0x70, 0x00, 0x00},
    }};

    reset();
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
    if      (addr < 0xFF15) (dynamic_cast<Channel*>(&square1)->*regwrite_ptr[i])(value);
    else if (addr < 0xFF1A) (dynamic_cast<Channel*>(&square2)->*regwrite_ptr[i])(value);
    else if (addr < 0xFF1F) (dynamic_cast<Channel*>(&wave   )->*regwrite_ptr[i])(value);
    else if (addr < 0xFF24) (dynamic_cast<Channel*>(&noise  )->*regwrite_ptr[i])(value);
    else if (addr < 0xFF27) {
        if      (i == 0) NR50_write(value);
        else if (i == 1) NR51_write(value);
        else if (i == 2) NR52_write(value);
    } else if(addr >= 0xFF30 && addr <= 0xFF3F) {
        // The wave table has 32 samples, but pairs of samples share the
        // same address. So we need to shift the value & double the address offset
        wave.set_sample((value >> 4) & 0xF, (addr - 0xFF30)*2);
        wave.set_sample(value & 0xF, (addr - 0xFF30)*2 + 1);
    }
}

uint8_t APU::register_read(uint16_t addr)
{
    assert(addr >= 0xFF10 && addr <= 0xFF3F);

    uint8_t i = (addr - 0xFF10) % 5;
    if      (addr < 0xFF15) return (dynamic_cast<Channel*>(&square1)->*regread_ptr[i])() | register_mask[0][i];
    else if (addr < 0xFF1A) return (dynamic_cast<Channel*>(&square2)->*regread_ptr[i])() | register_mask[1][i];
    else if (addr < 0xFF1F) return (dynamic_cast<Channel*>(&wave   )->*regread_ptr[i])() | register_mask[2][i];
    else if (addr < 0xFF24) return (dynamic_cast<Channel*>(&noise  )->*regread_ptr[i])() | register_mask[3][i];
    else if (addr < 0xFF27) {
        if      (i == 0) return NR50_read() | register_mask[4][i];
        else if (i == 1) return NR51_read() | register_mask[4][i];
        else if (i == 2) return NR52_read() | register_mask[4][i];
    } else if(addr >= 0xFF30 && addr <= 0xFF3F) {
        return (wave.get_sample((addr - 0xFF30)*2) << 4)
                | wave.get_sample((addr - 0xFF30)*2 + 1);
    }

    // The rest are undefined addresses that just return all 1s
    return 0xFF;
}

void APU::reset()
{
    // Default values
    // NR1x
    register_write(0xFF10, 0x80);
    register_write(0xFF11, 0xBF);
    register_write(0xFF12, 0xF3);
    register_write(0xFF14, 0xBF);

    // NR2x
    register_write(0xFF16, 0x3F);
    register_write(0xFF17, 0x00);
    register_write(0xFF19, 0xBF);

    // NR3x
    register_write(0xFF1A, 0x7F);
    register_write(0xFF1B, 0xFF);
    register_write(0xFF1C, 0x9F);
    register_write(0xFF1E, 0xBF);

    // NR4x
    register_write(0xFF20, 0xFF);
    register_write(0xFF21, 0x00);
    register_write(0xFF22, 0x00);
    register_write(0xFF23, 0xBF);

    // NR5x
    register_write(0xFF24, 0x77);
    register_write(0xFF25, 0xF3);
    register_write(0xFF26, 0xF1);

    // Wave table
    register_write(0xFF30, 0x84);
    register_write(0xFF31, 0x40);
    register_write(0xFF32, 0x43);
    register_write(0xFF33, 0xAA);
    register_write(0xFF34, 0x2D);
    register_write(0xFF35, 0x78);
    register_write(0xFF36, 0x92);
    register_write(0xFF37, 0x3C);
    register_write(0xFF38, 0x60);
    register_write(0xFF39, 0x59);
    register_write(0xFF3A, 0x59);
    register_write(0xFF3B, 0xB0);
    register_write(0xFF3C, 0x34);
    register_write(0xFF3D, 0xB8);
    register_write(0xFF3E, 0x2E);
    register_write(0xFF3F, 0xDA);
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

    // We don't use these for anything, other than returning them in NR50_read
    this->vin_left = vin_left;
    this->vin_right = vin_right;

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

uint8_t APU::NR50_read()
{
    uint8_t volume_left = mixer.get_master_volume_left();
    uint8_t volume_right = mixer.get_master_volume_right();
    return (vin_left << 7) | (volume_left << 4) | (vin_right << 3) | volume_right;
}

uint8_t APU::NR51_read()
{
    uint8_t noise_left = noise.is_left_speaker_enabled();
    uint8_t noise_right = noise.is_right_speaker_enabled();
    uint8_t wave_left = wave.is_left_speaker_enabled();
    uint8_t wave_right = wave.is_right_speaker_enabled();
    uint8_t square2_left = square2.is_left_speaker_enabled();
    uint8_t square2_right = square2.is_right_speaker_enabled();
    uint8_t square1_left = square1.is_left_speaker_enabled();
    uint8_t square1_right = square1.is_right_speaker_enabled();
    return (noise_left << 7) | (wave_left << 6) | (square2_left << 5) | (square1_left << 4) |
           (noise_right << 3) | (wave_right << 2) | (square2_right << 1) | square1_right;
}

uint8_t APU::NR52_read()
{
    uint8_t noise_enabled = noise.is_channel_enabled();
    uint8_t wave_enabled = wave.is_channel_enabled();
    uint8_t square2_enabled = square2.is_channel_enabled();
    uint8_t square1_enabled = square1.is_channel_enabled();
    return (power_on << 7) | (noise_enabled << 3) | (wave_enabled << 2) | (square2_enabled << 1) | square1_enabled;
}
