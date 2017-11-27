#pragma once

#include <string>
#include <vector>
#include <exception>

class ParsingError : public std::runtime_error {
public:
    ParsingError(const std::string& message)
        : std::runtime_error(message) {}
};

struct GBSContent {
    uint8_t version;
    uint8_t num_songs;
    uint8_t first_song;
    uint16_t load_addr;
    uint16_t init_addr;
    uint16_t play_addr;
    uint16_t stack_pointer;
    uint8_t timer_modulo;
    uint8_t timer_control;
    std::string title;
    std::string author;
    std::string copyright;
    std::vector<uint8_t> code;
};

class GBSReader
{
public:
    void load_file(std::string filename);
    GBSContent& get_content();

    void print_metadata(bool verbose = true);

private:
    GBSContent content;

    void parse_file(std::vector<uint8_t>& buf);
};
