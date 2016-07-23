#include <gtest/gtest.h>

#include "punycode.h"

TEST(PunycoderTest, NeedsPunycoding)
{
    EXPECT_EQ(false, Url::Punycode::needsPunycoding("totally safe string"));
    EXPECT_EQ(true, Url::Punycode::needsPunycoding("pas sécurisé"));
}

TEST(PunycoderTest, Arabic)
{
    std::string example = "\xd9\x84\xd9\x8a\xd9\x87\xd9\x85\xd8\xa7"
          "\xd8\xa8\xd8\xaa\xd9\x83\xd9\x84\xd9\x85\xd9\x88\xd8\xb4"
          "\xd8\xb9\xd8\xb1\xd8\xa8\xd9\x8a\xd8\x9f";
    std::string expected = "egbpdaj6bu4bxfgehfvwxn";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, ChineseSimplified)
{
    std::string example = "\xe4\xbb\x96\xe4\xbb\xac\xe4\xb8\xba\xe4"
          "\xbb\x80\xe4\xb9\x88\xe4\xb8\x8d\xe8\xaf\xb4\xe4\xb8\xad"
          "\xe6\x96\x87";
    std::string expected = "ihqwcrb4cv8a8dqg056pqjye";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, ChineseTraditional)
{
    std::string example = "\xe4\xbb\x96\xe5\x80\x91\xe7\x88\xb2\xe4"
          "\xbb\x80\xe9\xba\xbd\xe4\xb8\x8d\xe8\xaa\xaa\xe4\xb8\xad"
          "\xe6\x96\x87";
    std::string expected = "ihqwctvzc91f659drss3x8bo0yb";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, Czech)
{
    std::string example = "Pro\xc4\x8dprost\xc4\x9bnemluv\xc3\xad\xc4\x8d" "esky";
    std::string expected = "Proprostnemluvesky-uyb24dma41a";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, Hebrew)
{
    std::string example = "\xd7\x9c\xd7\x9e\xd7\x94\xd7\x94\xd7\x9d"
          "\xd7\xa4\xd7\xa9\xd7\x95\xd7\x98\xd7\x9c\xd7\x90\xd7\x9e"
          "\xd7\x93\xd7\x91\xd7\xa8\xd7\x99\xd7\x9d\xd7\xa2\xd7\x91"
          "\xd7\xa8\xd7\x99\xd7\xaa";
    std::string expected = "4dbcagdahymbxekheh6e0a7fei0b";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, Hindi)
{
    std::string example = "\xe0\xa4\xaf\xe0\xa4\xb9\xe0\xa4\xb2\xe0"
          "\xa5\x8b\xe0\xa4\x97\xe0\xa4\xb9\xe0\xa4\xbf\xe0\xa4\xa8"
          "\xe0\xa5\x8d\xe0\xa4\xa6\xe0\xa5\x80\xe0\xa4\x95\xe0\xa5"
          "\x8d\xe0\xa4\xaf\xe0\xa5\x8b\xe0\xa4\x82\xe0\xa4\xa8\xe0"
          "\xa4\xb9\xe0\xa5\x80\xe0\xa4\x82\xe0\xa4\xac\xe0\xa5\x8b"
          "\xe0\xa4\xb2\xe0\xa4\xb8\xe0\xa4\x95\xe0\xa4\xa4\xe0\xa5"
          "\x87\xe0\xa4\xb9\xe0\xa5\x88\xe0\xa4\x82";
    std::string expected = "i1baa7eci9glrd9b2ae1bj0hfcgg6iyaf8o0a1dig0cd";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, Japanese)
{
    std::string example = "\xe3\x81\xaa\xe3\x81\x9c\xe3\x81\xbf\xe3"
          "\x82\x93\xe3\x81\xaa\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e"
          "\xe3\x82\x92\xe8\xa9\xb1\xe3\x81\x97\xe3\x81\xa6\xe3\x81"
          "\x8f\xe3\x82\x8c\xe3\x81\xaa\xe3\x81\x84\xe3\x81\xae\xe3"
          "\x81\x8b";
    std::string expected = "n8jok5ay5dzabd5bym9f0cm5685rrjetr6pdxa";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, Korean)
{
    std::string example = "\xec\x84\xb8\xea\xb3\x84\xec\x9d\x98\xeb"
          "\xaa\xa8\xeb\x93\xa0\xec\x82\xac\xeb\x9e\x8c\xeb\x93\xa4"
          "\xec\x9d\xb4\xed\x95\x9c\xea\xb5\xad\xec\x96\xb4\xeb\xa5"
          "\xbc\xec\x9d\xb4\xed\x95\xb4\xed\x95\x9c\xeb\x8b\xa4\xeb"
          "\xa9\xb4\xec\x96\xbc\xeb\xa7\x88\xeb\x82\x98\xec\xa2\x8b"
          "\xec\x9d\x84\xea\xb9\x8c";
    std::string expected =
        "989aomsvi5e83db1d2a355cv1e0vak1dwrv93d5xbh15a0dt30a5jpsd879ccm6fea98c";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, Russian)
{
    std::string example = "\xd0\xbf\xd0\xbe\xd1\x87\xd0\xb5\xd0\xbc"
          "\xd1\x83\xd0\xb6\xd0\xb5\xd0\xbe\xd0\xbd\xd0\xb8\xd0\xbd"
          "\xd0\xb5\xd0\xb3\xd0\xbe\xd0\xb2\xd0\xbe\xd1\x80\xd1\x8f"
          "\xd1\x82\xd0\xbf\xd0\xbe\xd1\x80\xd1\x83\xd1\x81\xd1\x81"
          "\xd0\xba\xd0\xb8";
    std::string expected = "b1abfaaepdrnnbgefbadotcwatmq2g4l";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, Spanish)
{
    std::string example = "Porqu\xc3\xa9nopuedensimplementehablarenEspa\xc3\xb1ol";
    std::string expected = "PorqunopuedensimplementehablarenEspaol-fmd56a";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, Vietnamese)
{
    std::string example = "T\xe1\xba\xa1isaoh\xe1\xbb\x8dkh\xc3\xb4"
          "ngth\xe1\xbb\x83" "ch\xe1\xbb\x89n\xc3\xb3iti\xe1\xba\xbf"
          "ngVi\xe1\xbb\x87t";
    std::string expected = "TisaohkhngthchnitingVit-kjcr8268qyxafd2f1b9g";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, RFC3492ExampleL)
{
    std::string example = "3\xe5\xb9\xb4" "B\xe7\xb5\x84\xe9\x87\x91"
          "\xe5\x85\xab\xe5\x85\x88\xe7\x94\x9f";
    std::string expected = "3B-ww4c5e180e575a65lsy2b";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, RFC3492ExampleM)
{
    std::string example = "\xe5\xae\x89\xe5\xae\xa4\xe5\xa5\x88\xe7"
          "\xbe\x8e\xe6\x81\xb5-with-SUPER-MONKEYS";
    std::string expected = "-with-SUPER-MONKEYS-pc58ag80a8qai00g7n9n";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, RFC3492ExampleN)
{
    std::string example = "Hello-Another-Way-\xe3\x81\x9d\xe3\x82"
            "\x8c\xe3\x81\x9e\xe3\x82\x8c\xe3\x81\xae\xe5\xa0\xb4"
            "\xe6\x89\x80";
    std::string expected = "Hello-Another-Way--fc4qua05auwb3674vfr0b";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, RFC3492ExampleO)
{
    std::string example = "\xe3\x81\xb2\xe3\x81\xa8\xe3\x81\xa4"
          "\xe5\xb1\x8b\xe6\xa0\xb9\xe3\x81\xae\xe4\xb8\x8b" "2";
    std::string expected = "2-u9tlzr9756bt3uc0v";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, RFC3492ExampleP)
{
    std::string example = "Maji\xe3\x81\xa7Koi\xe3\x81\x99\xe3\x82"
          "\x8b" "5\xe7\xa7\x92\xe5\x89\x8d";
    std::string expected = "MajiKoi5-783gue6qz075azm5e";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, RFC3492ExampleQ)
{
    std::string example = "\xe3\x83\x91\xe3\x83\x95\xe3\x82\xa3\xe3"
          "\x83\xbc" "de\xe3\x83\xab\xe3\x83\xb3\xe3\x83\x90";
    std::string expected = "de-jg4avhby1noc0d";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, RFC3492ExampleR)
{
    std::string example = "\xe3\x81\x9d\xe3\x81\xae\xe3\x82\xb9\xe3"
          "\x83\x94\xe3\x83\xbc\xe3\x83\x89\xe3\x81\xa7";
    std::string expected = "d9juau41awczczp";
    EXPECT_EQ(expected, Url::Punycode::encode(std::string(example)));
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, DecodeCaseInsensitivity)
{
    std::string example = "\xe3\x81\x9d\xe3\x81\xae\xe3\x82\xb9\xe3"
          "\x83\x94\xe3\x83\xbc\xe3\x83\x89\xe3\x81\xa7";
    std::string expected = "D9JUAU41AWCZCZP";
    EXPECT_EQ(example, Url::Punycode::decode(std::string(expected)));
}

TEST(PunycoderTest, EncodeOverflowDelta)
{
    // The 'n' must take on a value of O(length(string) * highest codepoint). The only way
    // to exercise that, then, with a bounded codepoint (unicode max is 0x10FFFF), is with
    // a very long string.
    //
    // std::numeric_limits<Punycoder::punycode_t>::max() / 0x10FFFF = 3855 (min length)
    std::string example(3855, 'a');
    example.append("\xF4\x8F\xBF\xBF");
    ASSERT_THROW(Url::Punycode::encode(example), std::invalid_argument);
}

TEST(PunycoderTest, EncodeOverflowDeltaIncrement)
{
    // The 'delta' takes on a value of O(length(string) * (n - last_n)). And then it's
    // incremented based on its offset in the codepoints. The case we need to exercise is
    // when that increment delta into overflow (rather than the multiplication step).
    //
    // The value of the delta is length(string) + (n - last_n), so I picked 8192 as the
    // string length (in code points) giving 524288 as the delta. The smallest 'n' value
    // is 128 (the first non-basic code point), encoded as "\xC2\x80", so the next
    // character point has to be 524416, encoded as "\xF2\x80\x82\x80".
    //
    // This makes delta = std::numeric_limits<Punycoder::punycode_t>::max() at the start
    // of the loop that walks the codepoints (incrementing 'i'), causing the targeted
    // overflow.
    std::string example = std::string(8190, 'a') + "\xC2\x80\xF2\x80\x82\x80";
    ASSERT_THROW(Url::Punycode::encode(example), std::invalid_argument);
}

TEST(PunycoderTest, DecodeEarlyTermination)
{
    // This is the example from RFC3492ExampleR, but missing the last letter
    std::string example = "d9juau41awczcz";
    ASSERT_THROW(Url::Punycode::decode(example), std::invalid_argument);
}

TEST(PunycoderTest, DecodeNonBasicCodePoint)
{
    // Punycoded strings should only have basic codepoints
    std::string example = "\xc3\xbc-";
    ASSERT_THROW(Url::Punycode::decode(example), std::invalid_argument);
}

TEST(PunycoderTest, DecodeNonBase36Char)
{
    // The punycoded bits have to use base36 chars: A-Z, a-z, 0-9
    std::string example = "/";
    ASSERT_THROW(Url::Punycode::decode(example), std::invalid_argument);
}

TEST(PunycoderTest, DecodeOverflowI)
{
    // This was the (seemingly) smallest reproducing substring from a random string
    // that exercises the overflow of 'i'.
    std::string example = "s121kz41webp2qdk6492joxumu36";
    ASSERT_THROW(Url::Punycode::decode(example), std::invalid_argument);
}

TEST(PunycoderTest, DecodeOverflowN)
{
    // To accomplish this, we must overflow n with a series of non-overflowing deltas
    std::string example("999999b");
    for (unsigned int i = 0; i < 5; ++i)
    {
        example.append(example);
    }
    ASSERT_THROW(Url::Punycode::decode(example), std::invalid_argument);
}
