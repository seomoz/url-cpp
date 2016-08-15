#include <gtest/gtest.h>

#include <fstream>

#include "psl.h"

class PSLProvidedExample : public ::testing::Test
{
protected:
    Url::PSL& getPSL()
    {
        static Url::PSL psl = Url::PSL::fromPath("test/fixtures/test-psl/psl");
        return psl;
    }
};

TEST(PSLTest, PathDoesNotExist)
{
    ASSERT_THROW(Url::PSL::fromPath("this/path/does/not/exist"), std::invalid_argument);
}

TEST(PSLTest, InvalidWildcard)
{
    ASSERT_THROW(Url::PSL::fromString("*"), std::invalid_argument);
    ASSERT_THROW(Url::PSL::fromString("*."), std::invalid_argument);
}

TEST(PSLTest, InvalidException)
{
    ASSERT_THROW(Url::PSL::fromString("!"), std::invalid_argument);
}

TEST_F(PSLProvidedExample, EmptySegments)
{
    std::string example = "empty..co.uk";
    ASSERT_THROW(getPSL().getPLD(example), std::invalid_argument);
}

TEST_F(PSLProvidedExample, MixedCaseOneSegment)
{
    std::string example = "COM";
    std::string tld = "com";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, MixedCaseTwoSegments)
{
    std::string example = "example.COM";
    std::string pld = "example.com";
    std::string tld = "com";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, MixedCaseThreeSegments)
{
    std::string example = "WwW.example.COM";
    std::string pld = "example.com";
    std::string tld = "com";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, LeadingDotCom)
{
    std::string example = ".com";
    std::string tld = "com";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, LeadingDotExample)
{
    std::string example = ".example";
    std::string tld = "example";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, LeadingDotExampleCom)
{
    std::string example = ".example.com";
    std::string pld = "example.com";
    std::string tld = "com";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, LeadingDotExampleExample)
{
    std::string example = ".example.example";
    std::string pld = "example.example";
    std::string tld = "example";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, UnlistedTLDOneSegment)
{
    std::string example = "example";
    std::string tld = "example";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, UnlistedTLDTwoSegments)
{
    std::string example = "example.example";
    std::string pld = "example.example";
    std::string tld = "example";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, UnlistedTLDThreeSegments)
{
    std::string example = "b.example.example";
    std::string pld = "example.example";
    std::string tld = "example";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, UnlistedTLDFourSegments)
{
    std::string example = "a.b.example.example";
    std::string pld = "example.example";
    std::string tld = "example";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, OneLevelRuleOneSegment)
{
    std::string example = "biz";
    std::string tld = "biz";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, OneLevelRuleTwoSegments)
{
    std::string example = "domain.biz";
    std::string pld = "domain.biz";
    std::string tld = "biz";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, OneLevelRuleThreeSegments)
{
    std::string example = "b.domain.biz";
    std::string pld = "domain.biz";
    std::string tld = "biz";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, OneLevelRuleFourSegments)
{
    std::string example = "a.b.domain.biz";
    std::string pld = "domain.biz";
    std::string tld = "biz";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, TwoLevelRuleComOneSegment)
{
    std::string example = "com";
    std::string tld = "com";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, TwoLevelRuleComTwoSegments)
{
    std::string example = "example.com";
    std::string pld = "example.com";
    std::string tld = "com";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, TwoLevelRuleComThreeSegments)
{
    std::string example = "b.example.com";
    std::string pld = "example.com";
    std::string tld = "com";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, TwoLevelRuleComFourSegments)
{
    std::string example = "a.b.example.com";
    std::string pld = "example.com";
    std::string tld = "com";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, TwoLevelRuleUkTwoSegments)
{
    std::string example = "uk.com";
    std::string tld = "uk.com";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, TwoLevelRuleUkThreeSegments)
{
    std::string example = "example.uk.com";
    std::string pld = "example.uk.com";
    std::string tld = "uk.com";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, TwoLevelRuleUkFourSegments)
{
    std::string example = "b.example.uk.com";
    std::string pld = "example.uk.com";
    std::string tld = "uk.com";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, TwoLevelRuleUkFiveSegments)
{
    std::string example = "a.b.example.uk.com";
    std::string pld = "example.uk.com";
    std::string tld = "uk.com";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, TwoLevelRuleNoMatch)
{
    std::string example = "test.ac";
    std::string pld = "test.ac";
    std::string tld = "ac";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, OneWildcardOneSegment)
{
    std::string example = "mm";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(Url::PSL::not_found, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, OneWildcardTwoSegments)
{
    std::string example = "c.mm";
    std::string tld = "c.mm";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, OneWildcardThreeSegments)
{
    std::string example = "b.c.mm";
    std::string pld = "b.c.mm";
    std::string tld = "c.mm";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, OneWildcardFourSegments)
{
    std::string example = "a.b.c.mm";
    std::string pld = "b.c.mm";
    std::string tld = "c.mm";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDOneSegment)
{
    std::string example = "jp";
    std::string tld = "jp";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDTwoSegments)
{
    std::string example = "test.jp";
    std::string pld = "test.jp";
    std::string tld = "jp";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDThreeSegments)
{
    std::string example = "www.test.jp";
    std::string pld = "test.jp";
    std::string tld = "jp";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDTwoSegmentRuleOneSegment)
{
    std::string example = "ac.jp";
    std::string tld = "ac.jp";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDTwoSegmentRuleTwoSegments)
{
    std::string example = "test.ac.jp";
    std::string pld = "test.ac.jp";
    std::string tld = "ac.jp";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDTwoSegmentRuleThreeSegments)
{
    std::string example = "www.test.ac.jp";
    std::string pld = "test.ac.jp";
    std::string tld = "ac.jp";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDKyotoOneSegment)
{
    std::string example = "kyoto.jp";
    std::string tld = "kyoto.jp";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDKyotoTwoSegments)
{
    std::string example = "test.kyoto.jp";
    std::string pld = "test.kyoto.jp";
    std::string tld = "kyoto.jp";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDKyotoThreeSegments)
{
    std::string example = "ide.kyoto.jp";
    std::string tld = "ide.kyoto.jp";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDKyotoFourSegments)
{
    std::string example = "b.ide.kyoto.jp";
    std::string pld = "b.ide.kyoto.jp";
    std::string tld = "ide.kyoto.jp";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDKyotoFiveSegments)
{
    std::string example = "a.b.ide.kyoto.jp";
    std::string pld = "b.ide.kyoto.jp";
    std::string tld = "ide.kyoto.jp";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDKobeThreeSegments)
{
    std::string example = "c.kobe.jp";
    std::string tld = "c.kobe.jp";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDKobeFourSegments)
{
    std::string example = "b.c.kobe.jp";
    std::string pld = "b.c.kobe.jp";
    std::string tld = "c.kobe.jp";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDKobeFiveSegments)
{
    std::string example = "a.b.c.kobe.jp";
    std::string pld = "b.c.kobe.jp";
    std::string tld = "c.kobe.jp";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDKobeCity)
{
    std::string example = "city.kobe.jp";
    std::string pld = "city.kobe.jp";
    std::string tld = "kobe.jp";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, MoreComplexTLDKobeCityWww)
{
    std::string example = "www.city.kobe.jp";
    std::string pld = "city.kobe.jp";
    std::string tld = "kobe.jp";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, WildcardWithExceptionsOneSegment)
{
    std::string example = "ck";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(Url::PSL::not_found, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, WildcardWithExceptionsTwoSegments)
{
    std::string example = "test.ck";
    std::string tld = "test.ck";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, WildcardWithExceptionsThreeSegments)
{
    std::string example = "b.test.ck";
    std::string pld = "b.test.ck";
    std::string tld = "test.ck";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, WildcardWithExceptionsFourSegments)
{
    std::string example = "a.b.test.ck";
    std::string pld = "b.test.ck";
    std::string tld = "test.ck";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, WildcardWithExceptionsExceptionTwoSegments)
{
    std::string example = "www.ck";
    std::string pld = "www.ck";
    std::string tld = "ck";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, WildcardWithExceptionsExceptionThreeSegments)
{
    std::string example = "www.www.ck";
    std::string pld = "www.ck";
    std::string tld = "ck";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, USK12OneSegment)
{
    std::string example = "us";
    std::string tld = "us";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, USK12TwoSegments)
{
    std::string example = "test.us";
    std::string pld = "test.us";
    std::string tld = "us";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, USK12ThreeSegments)
{
    std::string example = "www.test.us";
    std::string pld = "test.us";
    std::string tld = "us";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, USK12StateTwoSegments)
{
    std::string example = "ak.us";
    std::string tld = "ak.us";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, USK12StateThreeSegments)
{
    std::string example = "test.ak.us";
    std::string pld = "test.ak.us";
    std::string tld = "ak.us";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, USK12StateFourSegments)
{
    std::string example = "www.test.ak.us";
    std::string pld = "test.ak.us";
    std::string tld = "ak.us";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, USK12K12StateThreeSegments)
{
    std::string example = "k12.ak.us";
    std::string tld = "k12.ak.us";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, USK12K12StateFourSegments)
{
    std::string example = "test.k12.ak.us";
    std::string pld = "test.k12.ak.us";
    std::string tld = "k12.ak.us";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, USK12K12StateFiveSegments)
{
    std::string example = "www.test.k12.ak.us";
    std::string pld = "test.k12.ak.us";
    std::string tld = "k12.ak.us";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, UnpunycodedIDNOneIDNSegment)
{
    std::string example = "\xe9\xa3\x9f\xe7\x8b\xae.com.cn";
    std::string pld = "\xe9\xa3\x9f\xe7\x8b\xae.com.cn";
    std::string tld = "com.cn";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, UnpunycodedIDNTwoIDNSegments)
{
    std::string example = "\xe9\xa3\x9f\xe7\x8b\xae.\xe5\x85\xac\xe5\x8f\xb8.cn";
    std::string pld = "\xe9\xa3\x9f\xe7\x8b\xae.\xe5\x85\xac\xe5\x8f\xb8.cn";
    std::string tld = "\xe5\x85\xac\xe5\x8f\xb8.cn";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, UnpunycodedIDNTwoIDNSegmentsWww)
{
    std::string example = "www.\xe9\xa3\x9f\xe7\x8b\xae.\xe5\x85\xac\xe5\x8f\xb8.cn";
    std::string pld = "\xe9\xa3\x9f\xe7\x8b\xae.\xe5\x85\xac\xe5\x8f\xb8.cn";
    std::string tld = "\xe5\x85\xac\xe5\x8f\xb8.cn";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, UnpunycodedIDNOneIDNSegmentShishi)
{
    std::string example = "shishi.\xe5\x85\xac\xe5\x8f\xb8.cn";
    std::string pld = "shishi.\xe5\x85\xac\xe5\x8f\xb8.cn";
    std::string tld = "\xe5\x85\xac\xe5\x8f\xb8.cn";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, UnpunycodedIDNOneIDNRule)
{
    std::string example = "\xe5\x85\xac\xe5\x8f\xb8.cn";
    std::string tld = "\xe5\x85\xac\xe5\x8f\xb8.cn";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, UnpunycodedIDNWithIDNTLD)
{
    std::string example = "\xe9\xa3\x9f\xe7\x8b\xae.\xe4\xb8\xad\xe5\x9b\xbd";
    std::string pld = "\xe9\xa3\x9f\xe7\x8b\xae.\xe4\xb8\xad\xe5\x9b\xbd";
    std::string tld = "\xe4\xb8\xad\xe5\x9b\xbd";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, UnpunycodedIDNWithIDNTLDWww)
{
    std::string example = "www.\xe9\xa3\x9f\xe7\x8b\xae.\xe4\xb8\xad\xe5\x9b\xbd";
    std::string pld = "\xe9\xa3\x9f\xe7\x8b\xae.\xe4\xb8\xad\xe5\x9b\xbd";
    std::string tld = "\xe4\xb8\xad\xe5\x9b\xbd";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, UnpunycodedIDNWithIDNTLDShishi)
{
    std::string example = "shishi.\xe4\xb8\xad\xe5\x9b\xbd";
    std::string pld = "shishi.\xe4\xb8\xad\xe5\x9b\xbd";
    std::string tld = "\xe4\xb8\xad\xe5\x9b\xbd";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, UnpunycodedIDNWithIDNTLDOneSegment)
{
    std::string example = "\xe4\xb8\xad\xe5\x9b\xbd";
    std::string tld = "\xe4\xb8\xad\xe5\x9b\xbd";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, PunycodedIDNOneIDNSegment)
{
    std::string example = "xn--85x722f.com.cn";
    std::string pld = "xn--85x722f.com.cn";
    std::string tld = "com.cn";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, PunycodedIDNTwoIDNSegments)
{
    std::string example = "xn--85x722f.xn--55qx5d.cn";
    std::string pld = "xn--85x722f.xn--55qx5d.cn";
    std::string tld = "xn--55qx5d.cn";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, PunycodedIDNTwoIDNSegmentsWww)
{
    std::string example = "www.xn--85x722f.xn--55qx5d.cn";
    std::string pld = "xn--85x722f.xn--55qx5d.cn";
    std::string tld = "xn--55qx5d.cn";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, PunycodedIDNOneIDNSegmentShishi)
{
    std::string example = "shishi.xn--55qx5d.cn";
    std::string pld = "shishi.xn--55qx5d.cn";
    std::string tld = "xn--55qx5d.cn";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, PunycodedIDNOneIDNRule)
{
    std::string example = "xn--55qx5d.cn";
    std::string tld = "xn--55qx5d.cn";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}

TEST_F(PSLProvidedExample, PunycodedIDNWithIDNTLD)
{
    std::string example = "xn--85x722f.xn--fiqs8s";
    std::string pld = "xn--85x722f.xn--fiqs8s";
    std::string tld = "xn--fiqs8s";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, PunycodedIDNWithIDNTLDWww)
{
    std::string example = "www.xn--85x722f.xn--fiqs8s";
    std::string pld = "xn--85x722f.xn--fiqs8s";
    std::string tld = "xn--fiqs8s";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, PunycodedIDNWithIDNTLDShishi)
{
    std::string example = "shishi.xn--fiqs8s";
    std::string pld = "shishi.xn--fiqs8s";
    std::string tld = "xn--fiqs8s";
    EXPECT_EQ(pld, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
    EXPECT_EQ(std::make_pair(tld, pld), getPSL().getBoth(example));
}

TEST_F(PSLProvidedExample, PunycodedIDNWithIDNTLDOneSegment)
{
    std::string example = "xn--fiqs8s";
    std::string tld = "xn--fiqs8s";
    EXPECT_EQ(Url::PSL::not_found, getPSL().getPLD(example));
    EXPECT_EQ(tld, getPSL().getTLD(example));
}
