#include <iostream>
#include "gameboy.h"

int main()
{
    GameBoy game_boy;
    Player player(game_boy.get_mixer());

    try {
        player.init();
    } catch (std::exception& e) {
        std::cout << e.what() << "\n";
        return 1;
    };

    game_boy.set_player(&player);

    // Infinite loop
    game_boy.run();

    return 0;
}
