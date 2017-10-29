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

GBSContent& GBSReader::get_content()
{
    return content;
}

void GBSReader::parse_file(std::vector<uint8_t>& buf)
{
    // Make sure that the file is at least as big as the header
    if (buf.size() < 0x70)
        throw ParsingError("Incomplete header (file too small)");

    // Check identifier string
    if (! (buf[0x0] == 'G' && buf[0x1] == 'B' && buf[0x2] == 'S'))
        throw ParsingError("File is not a GBS file");

    content.version = buf[0x3];
    content.num_songs = buf[0x4];
    content.first_song = buf[0x5];

    if (content.first_song >= content.num_songs)
        throw ParsingError("First song number >= number of songs");

    content.load_addr = (buf[0x7] << 8) | buf[0x6];
    if (content.load_addr < 0x0400 || content.load_addr > 0x7FFF)
        throw ParsingError("Invalid load adress");

    content.init_addr = (buf[0x9] << 8) | buf[0x8];
    if (content.init_addr < 0x0400 || content.init_addr > 0x7FFF)
        throw ParsingError("Invalid init adress");

    content.play_addr = (buf[0xB] << 8) | buf[0xA];
    if (content.play_addr < 0x0400 || content.play_addr > 0x7FFF)
        throw ParsingError("Invalid play adress");

    content.stack_pointer = (buf[0xD] << 8) | buf[0xC];
    content.timer_modulo = buf[0xE];
    content.timer_control = buf[0xF];

    auto title_start = buf.begin() + 0x10;
    content.title = std::string(title_start, title_start + 0x19);

    auto author_start = buf.begin() + 0x30;
    content.title = std::string(author_start, author_start + 0x19);

    auto copyright_start = buf.begin() + 0x50;
    content.copyright = std::string(copyright_start, copyright_start + 0x19);

    auto code_start = buf.begin() + 0x70;
    content.code = std::vector<uint8_t>(code_start, buf.end());
}
