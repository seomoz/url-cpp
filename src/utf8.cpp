#include <algorithm>
#include <string>
#include <iostream>

#include "utf8.h"

namespace Url
{

    Utf8::codepoint_t Utf8::readCodepoint(
        std::string::const_iterator& it, const std::string::const_iterator& end)
    {
        ++it;
        return 0;
    }

    std::string& Utf8::writeCodepoint(std::string& str, Utf8::codepoint_t value)
    {
        return str;
    }

};
