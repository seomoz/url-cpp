#include <gtest/gtest.h>

#include "url.h"

TEST(ParseTest, RelativePath)
{
    Url::Url parsed("foo");
    EXPECT_EQ("", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("foo", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
}

TEST(ParseTest, RelativePathWithExtras)
{
    Url::Url parsed("foo;params?query#fragment");
    EXPECT_EQ("", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("foo", parsed.path());
    EXPECT_EQ("params", parsed.params());
    EXPECT_EQ("query", parsed.query());
    EXPECT_EQ("fragment", parsed.fragment());
}

TEST(ParseTest, FullUrl)
{
    Url::Url parsed("http://foo.com/path");
    EXPECT_EQ("http", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("foo.com", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("/path", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
}

TEST(ParseTest, AbsoluteNoPath)
{
    Url::Url parsed("http://foo.com");
    EXPECT_EQ("http", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("foo.com", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
}

TEST(ParseTest, SchemeRelative)
{
    Url::Url parsed("//foo.com/path");
    EXPECT_EQ("", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("foo.com", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("/path", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
}

TEST(ParseTest, SchemeRelativeWithUserInfo)
{
    Url::Url parsed("//user:pass@foo.com/");
    EXPECT_EQ("", parsed.scheme());
    EXPECT_EQ("user:pass", parsed.userinfo());
    EXPECT_EQ("foo.com", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("/", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
}

TEST(ParseTest, UserInfo)
{
    Url::Url parsed("http://user:pass@foo.com/");
    EXPECT_EQ("http", parsed.scheme());
    EXPECT_EQ("user:pass", parsed.userinfo());
    EXPECT_EQ("foo.com", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("/", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
}

/* These are all from Python */
TEST(ParseTest, TestFile)
{
    Url::Url parsed("file:///tmp/junk.txt");
    EXPECT_EQ("file", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("/tmp/junk.txt", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
}

TEST(ParseTest, TestImap)
{
    Url::Url parsed("imap://mail.python.org/mbox1");
    EXPECT_EQ("imap", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("mail.python.org", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("/mbox1", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
}

TEST(ParseTest, TestMms)
{
    Url::Url parsed("mms://wms.sys.hinet.net/cts/Drama/09006251100.asf");
    EXPECT_EQ("mms", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("wms.sys.hinet.net", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("/cts/Drama/09006251100.asf", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
}

TEST(ParseTest, TestNfs)
{
    Url::Url parsed("nfs://server/path/to/file.txt");
    EXPECT_EQ("nfs", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("server", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("/path/to/file.txt", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
}

TEST(ParseTest, TestSvnOverSsh)
{
    Url::Url parsed("svn+ssh://svn.zope.org/repos/main/ZConfig/trunk/");
    EXPECT_EQ("svn+ssh", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("svn.zope.org", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("/repos/main/ZConfig/trunk/", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
}

TEST(ParseTest, TestGitOverSsh)
{
    Url::Url parsed("git+ssh://git@github.com/user/project.git");
    EXPECT_EQ("git+ssh", parsed.scheme());
    EXPECT_EQ("git", parsed.userinfo());
    EXPECT_EQ("github.com", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("/user/project.git", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
}

TEST(ParseTest, TestUppercaseScheme)
{
    Url::Url parsed("HTTP://WWW.PYTHON.ORG/doc/#frag");
    EXPECT_EQ("http", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("www.python.org", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("/doc/", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("frag", parsed.fragment());
}

TEST(ParseTest, TestPortLeadingZero)
{
    Url::Url parsed("http://www.python.org:080/");
    EXPECT_EQ("http", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("www.python.org", parsed.host());
    EXPECT_EQ(80, parsed.port());
    EXPECT_EQ("/", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
}

TEST(ParseTest, TestEmptyPort)
{
    Url::Url parsed("http://www.python.org:/");
    EXPECT_EQ("http", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("www.python.org", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("/", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
}

TEST(ParseTest, TestIllegalPort)
{
    ASSERT_THROW(Url::Url("http://www.python.org:65536/"), Url::UrlParseException);
}

TEST(ParseTest, TestNegativePort)
{
    ASSERT_THROW(Url::Url("http://www.python.org:-20/"), Url::UrlParseException);
}

TEST(ParseTest, TestPortOutOfRange)
{
    ASSERT_THROW(Url::Url("http://www.python.org:8589934592/"), Url::UrlParseException);
}

TEST(ParseTest, TestPortNotNumber)
{
    ASSERT_THROW(Url::Url("http://www.python.org:80hello/"), Url::UrlParseException);
}

TEST(HostnameTest, LowercasesHostname)
{
    EXPECT_EQ("www.testing.com", Url::Url("http://www.TESTING.coM").host());
    EXPECT_EQ("www.testing.com", Url::Url("http://WWW.testing.com").host());
    EXPECT_EQ("www.testing.com", Url::Url("http://www.testing.com/FOO").host());
}

TEST(QueryTest, SanitizesQuery)
{
    EXPECT_EQ("a=1&b=2"    , Url::Url("http://foo.com/?a=1&&&&&&b=2"   ).query());
    EXPECT_EQ("foo=2"      , Url::Url("http://foo.com/????foo=2"       ).query());
    EXPECT_EQ("foo=2"      , Url::Url("http://foo.com/?foo=2&&&"       ).query());
}

TEST(ParamTest, SanitizesParams)
{
    EXPECT_EQ(""           , Url::Url("http://foo.com/"                ).params());
    EXPECT_EQ("a=1;b=2"    , Url::Url("http://foo.com/;a=1;;;;;;b=2"   ).params());
    EXPECT_EQ("a=1;b=2"    , Url::Url("http://foo.com/;;;a=1;;;;;;b=2" ).params());
    EXPECT_EQ("a=1;b=2"    , Url::Url("http://foo.com/;a=1;;;;;;b=2;;;").params());
}

TEST(AbspathTest, BasicPath)
{
    EXPECT_EQ("/howdy",
        Url::Url("http://foo.com/howdy").abspath().path());
}

TEST(AbspathTest, RepeatedSeparator)
{
    EXPECT_EQ("/hello/how/are",
        Url::Url("http://foo.com/hello//how//are").abspath().path());
}

TEST(AbspathTest, ParentDirectory)
{
    EXPECT_EQ("/how/are",
        Url::Url("http://foo.com/hello/../how/are").abspath().path());
}

TEST(AbspathTest, ParentDirectoryWithRepeatedSeparators)
{
    EXPECT_EQ("/how/",
        Url::Url("http://foo.com/hello//..//how/").abspath().path());
}

TEST(AbspathTest, GrandparentDirectory)
{
    EXPECT_EQ("/c",
        Url::Url("http://foo.com/a/b/../../c").abspath().path());
}

TEST(AbspathTest, UpMoreLevelsThanSegments)
{
    EXPECT_EQ("/c",
        Url::Url("http://foo.com/../../../c").abspath().path());
}

TEST(AbspathTest, CurrentDirectory)
{
    EXPECT_EQ("/hello",
        Url::Url("http://foo.com/./hello").abspath().path());
}

TEST(AbspathTest, CurrentDirectoryRepeated)
{
    EXPECT_EQ("/hello",
        Url::Url("http://foo.com/./././hello").abspath().path());
}

TEST(AbspathTest, MultipleSegmentsDirectory)
{
    EXPECT_EQ("/a/b/c/",
        Url::Url("http://foo.com/a/b/c/").abspath().path());
}

TEST(AbspathTest, TrailingParentDirectory)
{
    EXPECT_EQ("/a/b/",
        Url::Url("http://foo.com/a/b/c/..").abspath().path());
}

TEST(AbspathTest, TrailingCurrentDirectory)
{
    EXPECT_EQ("/a/b/",
        Url::Url("http://foo.com/a/b/.").abspath().path());
}

TEST(AbspathTest, TrailingCurrentDirectoryMultiple)
{
    EXPECT_EQ("/a/b/",
        Url::Url("http://foo.com/a/b/./././").abspath().path());
}

TEST(AbspathTest, TrailingParentDirectorySlash)
{
    EXPECT_EQ("/a/",
        Url::Url("http://foo.com/a/b/../").abspath().path());
}

TEST(AbspathTest, OnlyCurrentDirectory)
{
    EXPECT_EQ("/",
        Url::Url("http://foo.com/.").abspath().path());
}

TEST(AbspathTest, OnlyMultipleParentDirectories)
{
    EXPECT_EQ("/",
        Url::Url("http://foo.com/../../..").abspath().path());
}

TEST(AbspathTest, TrailingDotInLastSegment)
{
    EXPECT_EQ("/whiz.",
        Url::Url("http://foo.com//foo/../whiz.").abspath().path());
}

TEST(AbspathTest, TrailingDotInSegmentSlash)
{
    EXPECT_EQ("/foo/whiz./",
        Url::Url("http://foo.com//foo/whiz./").abspath().path());
}

TEST(AbspathTest, TrailingDotInSegment)
{
    EXPECT_EQ("/foo/whiz./bar",
        Url::Url("http://foo.com//foo/whiz./bar").abspath().path());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
