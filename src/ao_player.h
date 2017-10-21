#pragma once

#include <ao/ao.h>
#include "mixer.h"

class AOPlayer
{
public:
    AOPlayer(Mixer& mixer);
    ~AOPlayer();

    // The ao init code is in this function instead of the constructor
    // because of the exception it may throw
    void init();

    // Play forever (until instance is destructed)
    void play();

private:
    Mixer& mixer;
	ao_device *device;
    bool playing;
};
