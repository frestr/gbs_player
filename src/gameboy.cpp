#include <chrono>
#include <thread>
#include <iostream>
#include "gameboy.h"

GameBoy::GameBoy(GBSContent& gbs_content)
    : apu(clock),
      cpu(apu)
{
    apu.run_tests();
    apu.reset();
    this->gbs_content = gbs_content;
}

void GameBoy::run()
{
    // Calculate timing constants
    const int buffer_threshold = apu.get_mixer().buffer_threshold / 2;
    const uint64_t clocks_per_period = (SystemClock::CLOCK_RATE / Mixer::SAMPLE_RATE) * buffer_threshold;
    const long int period = (static_cast<double>(buffer_threshold) / Mixer::SAMPLE_RATE) * 1000000000;
    std::chrono::nanoseconds period_duration(period);

    cpu.gbs_load(gbs_content.load_addr, gbs_content.code);
    cpu.gbs_init(gbs_content.init_addr, gbs_content.first_song, gbs_content.stack_pointer,
                 gbs_content.timer_modulo, gbs_content.timer_control);

    bool running = true;
    bool init_done = false;

#ifdef DEBUG
    std::cout << "INIT\n";
#endif

    uint32_t cycles;
    uint32_t instr_cycles;
    uint32_t interrupt_rate;
    uint32_t interrupt_counter;
    while (running) {
        auto start = std::chrono::steady_clock::now();

        interrupt_rate = cpu.get_interrupt_rate();

        cycles = 0;
        while (cycles < clocks_per_period) {
            if (! cpu.is_halted() && ! cpu.is_stopped() && ! cpu.procedure_done()) {
                instr_cycles = cpu.execute_instruction();
                cycles += instr_cycles;
                interrupt_counter += instr_cycles;

                for (uint8_t i = 0; i < instr_cycles; ++i)
                    clock.clock();
            } else {
                // We still need to run the clock, even if the CPU is halted/stopped
                // or the current music procedure is done
                clock.clock();
                ++cycles;
                ++interrupt_counter;
            }

            if (cpu.is_hanging()) {
                std::cout << "CPU is hanging. Quitting...\n";
                running = false;
                break;
            }

            // Run the play procedure at the end of INIT or at interrupt
            if ((cpu.procedure_done() && ! init_done) ||
                    (init_done && interrupt_counter >= interrupt_rate)) {
#ifdef DEBUG
                std::cout << "PLAY!\n";
#endif
                init_done = true;
                interrupt_counter = 0;
                cpu.gbs_play(gbs_content.play_addr);
            }
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
