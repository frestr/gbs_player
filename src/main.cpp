#include <iostream>
#include "gameboy.h"
#include "gbs_reader.h"
#include "cpu.h"

int main()
{
    GBSReader reader;
    try {
        reader.load_file("DMG-TRA-0.gbs");
    } catch (std::exception& e) {
        std::cout << "Error while loading file: " << e.what() << "\n";
        std::cout << "Quitting...\n";
        return 1;
    }

    GameBoy game_boy(reader.get_content());
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
