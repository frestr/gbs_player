#pragma once

#include "systemclock.h"
#include "apu.h"
#include "mixer.h"
#include "player.h"
#include "cpu.h"
#include "gbs_reader.h"

class GameBoy
{
public:
    GameBoy(GBSContent& gbs_content);

    // Main loop
    void run();

    // The player needs this. Not very elegant
    Mixer& get_mixer();

    void set_player(Player* player);

    void next_song();
    void prev_song();

private:
    SystemClock clock;
    APU apu;
    CPU cpu;
    Player* player;

    GBSContent gbs_content;

    uint8_t curr_song;

    std::atomic<bool> play_next_song;
    std::atomic<bool> play_prev_song;
};
