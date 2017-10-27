#include <chrono>
#include <thread>
#include <iostream>
#include "gameboy.h"

GameBoy::GameBoy()
    : apu(clock)
{
    apu.run_tests();
    apu.reset();
}

void GameBoy::run()
{
    // Calculate timing constants
    const int buffer_threshold = apu.get_mixer().buffer_threshold / 2;
    const int clocks_per_period = (SystemClock::CLOCK_RATE / Mixer::SAMPLE_RATE) * buffer_threshold;
    const long int period = (static_cast<double>(buffer_threshold) / Mixer::SAMPLE_RATE) * 1000000000;
    std::chrono::nanoseconds period_duration(period);
    
    apu.register_write(0xFF23, 0x80); // Turn APU power on
    apu.register_write(0xFF11, 0x80); // Set duty cycle
    apu.register_write(0xFF12, 0xF3); // Set full volume & period for square 1
    apu.register_write(0xFF25, 0xF3); // Enable both left/right output for square channels
    apu.register_write(0xFF24, 0x77); // Max master volume

    // Sound 1
    apu.register_write(0xFF13, 0x83); // Set lower freq for square 1
    apu.register_write(0xFF14, 0x87); // Set upper freq & trigger

    uint64_t a = 0;
    while (true) {
        auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < clocks_per_period; ++i) {
            // Wait a little
            if (a == 419430) {
                // Sound 2
                apu.register_write(0xFF13, 0xC1);
                apu.register_write(0xFF14, 0x87);
            } 
            clock.clock();
            ++a;
        }

        if (player != NULL)
            player->play();
        std::this_thread::sleep_until(start + period_duration);
    }
}

Mixer& GameBoy::get_mixer()
{
    return apu.get_mixer();
}

void GameBoy::set_player(Player* player)
{
    this->player = player;
}
