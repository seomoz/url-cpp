#ifndef PUNYCODE_CPP_H
#define PUNYCODE_CPP_H

#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace Url
{

    struct Punycoder
    {
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

        static long adapt(long delta, long numpoints, bool firsttime);

    };

}

#endif
