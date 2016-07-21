#include <gtest/gtest.h>

#include "utf8.h"

TEST(Utf8Test, Ascii)
{
    std::string str = "a";
    Url::Utf8::codepoint_t value = 97;
    EXPECT_EQ(value, Url::Utf8::toCodepoint(str));
    EXPECT_EQ(str, Url::Utf8::fromCodepoint(value));
}

TEST(Utf8Test, Umlaut)
{
    std::string str = "\xC3\xBC";
    // '\xc3\xbc'
    Url::Utf8::codepoint_t value = 252;
    EXPECT_EQ(value, Url::Utf8::toCodepoint(str));
    EXPECT_EQ(str, Url::Utf8::fromCodepoint(value));
}

TEST(Utf8Test, IntegralSymbol)
{
    std::string str = "\xE2\x88\xAB";
    Url::Utf8::codepoint_t value = 8747;
    EXPECT_EQ(value, Url::Utf8::toCodepoint(str));
    EXPECT_EQ(str, Url::Utf8::fromCodepoint(value));
}

TEST(Utf8Test, PhaistosDiscSignEagle)
{
    std::string str = "\xF0\x90\x87\xAE";
    Url::Utf8::codepoint_t value = 66030;
    EXPECT_EQ(value, Url::Utf8::toCodepoint(str));
    EXPECT_EQ(str, Url::Utf8::fromCodepoint(value));
}

TEST(Utf8Test, LowStartByte)
{
    // Corresponds to 10011101, but 10xxxxxx is a continuation byte
    std::string str = { static_cast<char>(0x9D) };
    ASSERT_THROW(Url::Utf8::toCodepoint(str), std::invalid_argument);
}

TEST(Utf8Test, HighStartByte)
{
    // Corresponds to 11111001, but 11110xxx is the highest start sequence
    std::string str = { static_cast<char>(0xF9) };
    ASSERT_THROW(Url::Utf8::toCodepoint(str), std::invalid_argument);
}

TEST(Utf8Test, SequenceTerminatedEarly)
{
    // Requests 3 additional bytes, but only one extra provided
    std::string str = { static_cast<char>(0xF0), static_cast<char>(0x8A) };
    ASSERT_THROW(Url::Utf8::toCodepoint(str), std::invalid_argument);
}

TEST(Utf8Test, InvalidContinuationByte)
{
    // Continuation byte is wrong -- must by 10xxxxxx, but is 1100xxxx
    std::string str = { static_cast<char>(0xF0), static_cast<char>(0xC0) };
    ASSERT_THROW(Url::Utf8::toCodepoint(str), std::invalid_argument);
}

TEST(Utf8Test, CodepointTooHigh)
{
    // Unicode codepoints are limited to 0x1FFFFF
    ASSERT_THROW(Url::Utf8::fromCodepoint(0x2FFFFF), std::invalid_argument);
}

TEST(Utf8Test, Arabic)
{
    std::string str = "\xD8\xA7\xD9\x84\xD8\xB9\xD8\xB1\xD8\xA8\xD9\x8A\xD8\xA9";
    std::vector<Url::Utf8::codepoint_t> codepoints = {
        0x0627, 0x0644, 0x0639, 0x0631, 0x0628, 0x064A, 0x0629
    };
    EXPECT_EQ(codepoints, Url::Utf8::toCodepoints(str));
    EXPECT_EQ(str, Url::Utf8::fromCodepoints(codepoints));
}

TEST(Utf8Test, Chinese)
{
    std::string str = "\xE4\xB8\xAD\xE6\x96\x87";
    std::vector<Url::Utf8::codepoint_t> codepoints = {
        0x4E2D, 0x6587
    };
    EXPECT_EQ(codepoints, Url::Utf8::toCodepoints(str));
    EXPECT_EQ(str, Url::Utf8::fromCodepoints(codepoints));
}

TEST(Utf8Test, Japanese)
{
    std::string str = "\xE6\x97\xA5\xE6\x9C\xAC\xE8\xAA\x9E";
    std::vector<Url::Utf8::codepoint_t> codepoints = {
        0x65E5, 0x672C, 0x8A9E
    };
    EXPECT_EQ(codepoints, Url::Utf8::toCodepoints(str));
    EXPECT_EQ(str, Url::Utf8::fromCodepoints(codepoints));
}
