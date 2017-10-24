#pragma once

#include <ao/ao.h>
#include "mixer.h"

class Player
{
public:
    Player(Mixer& mixer);
    ~Player();

    // The ao init code is in this function instead of the constructor
    // because of the exception it may throw
    void init();

    // Play forever (until instance is destructed)
    void play();

private:
    Mixer& mixer;
    ao_device *device;
    std::vector<int16_t> buf;
};
