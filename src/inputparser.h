#pragma once

#include <string>
#include <vector>

class InputParser
{
    public:
        InputParser(int argc, char* argv[]);
        bool GetOption(const std::string& option, std::string& value) const;

    private:
        std::vector<std::string> tokens_;
};
