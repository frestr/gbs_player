#include <chrono>
#include <thread>
#include <iostream>
#include "gameboy.h"

GameBoy::GameBoy(GBSContent& gbs_content)
    : apu(clock),
      cpu(apu)
{
    //apu.run_tests();
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

    bool testing = false;
    /* cpu.load_test_rom("instr_tests/01-special.gb");                  // PASSED */
    /* cpu.load_test_rom("instr_tests/02-interrupts.gb"); */
    /* cpu.load_test_rom("instr_tests/03-op sp,hl.gb");                 // PASSED */
    /* cpu.load_test_rom("instr_tests/04-op r,imm.gb");                 // PASSED */
    /* cpu.load_test_rom("instr_tests/05-op rp.gb");                    // PASSED */
    /* cpu.load_test_rom("instr_tests/06-ld r,r.gb");                   // PASSED */
    /* cpu.load_test_rom("instr_tests/07-jr,jp,call,ret,rst.gb");       // PASSED */
    /* cpu.load_test_rom("instr_tests/08-misc instrs.gb");              // PASSED */
    /* cpu.load_test_rom("instr_tests/09-op r,r.gb");                   // PASSED */
    /* cpu.load_test_rom("instr_tests/10-bit ops.gb");                  // PASSED */
    /* cpu.load_test_rom("instr_tests/11-op a,(hl).gb");                // PASSED */

    /* cpu.load_test_rom("sound_tests/01-registers.gb");                // PASSED */
    /* cpu.load_test_rom("sound_tests/02-len ctr.gb");                  // PASSED */
    /* cpu.load_test_rom("sound_tests/03-trigger.gb"); */
    /* cpu.load_test_rom("sound_tests/04-sweep.gb"); */
    /* cpu.load_test_rom("sound_tests/05-sweep details.gb"); */
    /* cpu.load_test_rom("sound_tests/06-overflow on trigger.gb"); */
    /* cpu.load_test_rom("sound_tests/07-len sweep period sync.gb"); */
    /* cpu.load_test_rom("sound_tests/08-len ctr during power.gb"); */
    /* cpu.load_test_rom("sound_tests/09-wave read while on.gb"); */
    /* cpu.load_test_rom("sound_tests/10-wave trigger while on.gb"); */
    /* cpu.load_test_rom("sound_tests/11-regs after power.gb"); */
    /* cpu.load_test_rom("sound_tests/12-wave write while on.gb"); */

    uint32_t cycles;
    uint32_t instr_cycles;
    uint32_t interrupt_rate;
    uint32_t interrupt_counter;
    while (running) {
        auto start = std::chrono::steady_clock::now();

        interrupt_rate = cpu.get_interrupt_rate();

        cycles = 0;
        while (cycles < clocks_per_period) {
            if (! cpu.is_halted() && ! cpu.is_stopped() && (testing || ! cpu.procedure_done())) {
                instr_cycles = cpu.execute_instruction();
                cycles += instr_cycles;
                interrupt_counter += instr_cycles;

                for (uint8_t i = 0; i < instr_cycles; ++i)
                    clock.clock();
            } else {
                // We still need to run the clock, even if the CPU is halted/stopped
                // or the current sound procedure is done
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
            if (! testing) {
                if ((cpu.procedure_done() && ! init_done) ||
                        (init_done && interrupt_counter >= interrupt_rate)) {
                    init_done = true;
                    interrupt_counter = 0;
                    cpu.gbs_play(gbs_content.play_addr);
                }
            }
        }

        if (! testing && player != NULL)
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
