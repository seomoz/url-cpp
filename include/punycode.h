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

    struct Punycoder
    {
        typedef Utf8::codepoint_t punycode_uint;

        static const unsigned int BASE          = 36;
        static const unsigned int TMIN          = 1;
        static const unsigned int TMAX          = 26;
        static const unsigned int SKEW          = 38;
        static const unsigned int DAMP          = 700;
        static const unsigned int INITIAL_BIAS  = 72;
        static const unsigned int INITIAL_N     = 128;

        // Codepoints to their base-36 value
        static const std::vector<int8_t> BASIC_TO_DIGIT;
        static const std::string DIGIT_TO_BASIC;

        // The highest codepoint in unicode
        static const punycode_uint MAX_PUNYCODE_UINT = std::numeric_limits<punycode_uint>::max();
        //Utf8::MAX_CODEPOINT;
        //std::numeric_limits<punycode_uint>::max();

        /**
         * Replace utf-8-encoded str into punycode.
         */
        static std::string& encode(std::string& str);

        /**
         * Create a new punycoded string from utf-8-encoded input.
         */
        static std::string encode(const std::string& str)
        {
            std::string result(str);
            encode(result);
            return result;
        }

        /**
         * Replace punycoded str into utf-8-encoded.
         */
        static std::string& decode(std::string& str);

        /**
         * Create a new utf-8-encoded string from punycoded input.
         */
        static std::string decode(const std::string& str)
        {
            std::string result(str);
            decode(result);
            return result;
        }

        /**
         * Determine if a string needs punycoding.
         */
        static bool needsPunycoding(const std::string& str);

    private:

        static punycode_uint adapt(
            punycode_uint delta, punycode_uint numpoints, bool firsttime);

    };

}

#endif
