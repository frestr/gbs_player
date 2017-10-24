#pragma once

#include "systemclock.h"
#include "apu.h"
#include "mixer.h"
#include "player.h"

class GameBoy
{
public:
    GameBoy();

    // Main loop
    void run();

    // The player needs this. Not very elegant
    Mixer& get_mixer();

    void set_player(Player* player);

private:
    SystemClock clock;
    APU apu;
    Player* player;
};
