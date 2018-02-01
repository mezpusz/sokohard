#include "inputparser.h"

InputParser::InputParser(int argc, char* argv[])
    : tokens_()
{
    for (int i = 1; i < argc; ++i)
    {
        tokens_.push_back(std::string(argv[i]));
    }
}

bool InputParser::GetOption(const std::string& option, std::string& value) const
{
    auto it = std::find(tokens_.begin(), tokens_.end(), option);
    if (it != tokens_.end() && ++it != tokens_.end())
    {
        value = *it;
        return true;
    }
    return false;
}
