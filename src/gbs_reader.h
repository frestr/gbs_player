#pragma once

#include <string>
#include <vector>
#include <exception>

class ParsingError : public std::runtime_error {
public:
    ParsingError(const std::string& message)
        : std::runtime_error(message) {}
};

class GBSReader
{
public:
    void load_file(std::string filename);

private:

    void parse_file(std::vector<uint8_t>& buf);
};
