#include <fstream>
#include <iterator>
#include <iostream>
#include "gbs_reader.h"

void GBSReader::load_file(std::string filename)
{
    std::ifstream file(filename, std::ios::binary);

    if (! file.is_open())
        throw std::runtime_error("Unable to open file");

    // Don't skip whitespace
    file.unsetf(std::ios::skipws);

    // Get file size
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Load file content into buffer
    std::vector<uint8_t> file_buf(size);
    file_buf.insert(file_buf.begin(),
                    std::istream_iterator<uint8_t>(file),
                    std::istream_iterator<uint8_t>());

    parse_file(file_buf);

    file.close();
}

void GBSReader::parse_file(std::vector<uint8_t>& buf)
{
    // Make sure that the file is at least as big as the header
    if (buf.size() < 0x70)
        throw ParsingError("Incomplete header (file too small)");

    // Check identifier string
    if (! (buf[0x0] == 'G' && buf[0x1] == 'B' && buf[0x2] == 'S'))
        throw ParsingError("File is not a GBS file");

    uint8_t version = buf[0x3];
    uint8_t num_songs = buf[0x4];
    uint8_t first_song = buf[0x5];

    if (first_song >= num_songs)
        throw ParsingError("First song number >= number of songs");

    uint16_t load_address = (buf[0x7] << 8) | buf[0x6];
    if (load_address < 0x0400 || load_address > 0x7FFF)
        throw ParsingError("Invalid load adress");

    uint16_t init_address = (buf[0x9] << 8) | buf[0x8];
    if (init_address < 0x0400 || init_address > 0x7FFF)
        throw ParsingError("Invalid init adress");

    uint16_t play_address = (buf[0xB] << 8) | buf[0xA];
    if (play_address < 0x0400 || play_address > 0x7FFF)
        throw ParsingError("Invalid play adress");

    uint16_t stack_pointer = (buf[0xD] << 8) | buf[0xC];
    uint8_t timer_modulo = buf[0xE];
    uint8_t timer_control = buf[0xF];

    auto title_start = buf.begin() + 0x10;
    std::string title(title_start, title_start + 0x19);

    auto author_start = buf.begin() + 0x30;
    std::string author(author_start, author_start + 0x19);

    auto copyright_start = buf.begin() + 0x50;
    std::string copyright(copyright_start, copyright_start + 0x19);

    auto code_start = buf.begin() + 0x70;
    std::vector<uint8_t> code(code_start, buf.end());
}
