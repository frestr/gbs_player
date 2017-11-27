#include <iostream>
#include <thread>
#include <termios.h>
#include "gameboy.h"
#include "gbs_reader.h"
#include "cpu.h"

struct termios old_term, new_term;

void init_termios()
{
    tcgetattr(0, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~ICANON;
    new_term.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &new_term);
}

void reset_termios()
{
    tcsetattr(0, TCSANOW, &old_term);
}

char getch()
{
    char ch;
    init_termios();
    ch = getchar();
    reset_termios();
    return ch;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <gbs-file>\n";
        return 1;
    }

    // Load the specified file
    GBSReader reader;
    try {
        reader.load_file(argv[1]);
    } catch (std::exception& e) {
        std::cout << "Error while loading file: " << e.what() << "\n";
        std::cout << "Quitting...\n";
        return 1;
    }

    // Print the file's metadata
    reader.print_metadata(true);

    GameBoy game_boy(reader.get_content());
    Player player(game_boy.get_mixer());

    // Initalize the sound player
    try {
        player.init();
    } catch (std::exception& e) {
        std::cout << e.what() << "\n";
        return 1;
    };

    game_boy.set_player(&player);

    // Run the game boy logic in a separate thread
    std::thread([&]() {
        game_boy.run();
    }).detach();

    // Poll for input commands
    char input;
    bool running = true;
    while(running) {
        input = getch();
        switch (input) {
            case 'n':
                game_boy.next_song();
                break;
            case 'p':
                game_boy.prev_song();
                break;
            case 'q':
                running = false;
                break;
        }
    }

    return 0;
}
