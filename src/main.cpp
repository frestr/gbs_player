#include <vector>
#include <iostream>
#include <chrono>
#include <cstring>
#include <ao/ao.h>
#include <thread>
#include "systemclock.h"
#include "apu.h"
#include "ao_player.h"

int main()
{
    SystemClock clock;
    APU apu(clock);
    AOPlayer player(apu.get_mixer());

    try {
        player.init();
    } catch (std::exception& e) {
        std::cout << e.what() << "\n";
        return 1;
    };

    clock.start();
    player.play();

    // All logic are done in separate threads
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
