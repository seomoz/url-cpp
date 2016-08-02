#ifndef PUNYCODE_CPP_H
#define PUNYCODE_CPP_H

#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "utf8.h"

namespace Url
{

    namespace Punycode
    {
        typedef Utf8::codepoint_t punycode_uint;

        const unsigned int BASE          = 36;
        const unsigned int TMIN          = 1;
        const unsigned int TMAX          = 26;
        const unsigned int SKEW          = 38;
        const unsigned int DAMP          = 700;
        const unsigned int INITIAL_BIAS  = 72;
        const unsigned int INITIAL_N     = 128;

        // Codepoints to their base-36 value
        const std::vector<int8_t> BASIC_TO_DIGIT = {
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            26, 27, 28, 29, 30, 31, 32, 33, 34, 35, -1, -1, -1, -1, -1, -1,

            -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,

            -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,

            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
        };
        const std::string DIGIT_TO_BASIC = "abcdefghijklmnopqrstuvwxyz0123456789";

        // The highest codepoint in unicode
        const punycode_uint MAX_PUNYCODE_UINT = std::numeric_limits<punycode_uint>::max();

        /**
         * Punycode the utf-8-encoded begin->end and append it to str.
         */
        std::string& encode(std::string& str, std::string::const_iterator begin,
            std::string::const_iterator end);

        /**
         * Replace utf-8-encoded str into punycode.
         */
        std::string& encode(std::string& str);

        /**
         * Create a new punycoded string from utf-8-encoded input.
         */
        std::string encode(const std::string& str);

        /**
         * Append the utf-8-version of the punycoded string between begin and end to str.
         */
        std::string& decode(std::string& str, std::string::const_iterator begin,
            std::string::const_iterator end);

        /**
         * Replace punycoded str into utf-8-encoded.
         */
        std::string& decode(std::string& str);

        /**
         * Create a new utf-8-encoded string from punycoded input.
         */
        std::string decode(const std::string& str);

        /**
         * Determine if a string needs punycoding.
         */
        bool needsPunycoding(const std::string& str);

        /**
         * Determine if the characters between these two iterators needs punycoding.
         */
        bool needsPunycoding(const std::string::const_iterator& begin,
                             const std::string::const_iterator& end);

        /**
         * Internal function for calculating bias.
         */
        punycode_uint adapt(
            punycode_uint delta, punycode_uint numpoints, bool firsttime);

    };

}

#endif
