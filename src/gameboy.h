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

private:
    SystemClock clock;
    APU apu;
    CPU cpu;
    Player* player;

    GBSContent gbs_content;
};
