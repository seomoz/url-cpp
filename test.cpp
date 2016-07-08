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
    EXPECT_EQ("foo", parsed.str());
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
    EXPECT_EQ("foo;params?query#fragment", parsed.str());
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
    EXPECT_EQ("http://foo.com/path", parsed.str());
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
    EXPECT_EQ("http://foo.com/", parsed.str());
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
    EXPECT_EQ("//foo.com/path", parsed.str());
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
    EXPECT_EQ("//user:pass@foo.com/", parsed.str());
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
    EXPECT_EQ("http://user:pass@foo.com/", parsed.str());
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
    EXPECT_EQ("file:///tmp/junk.txt", parsed.str());
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
    EXPECT_EQ("imap://mail.python.org/mbox1", parsed.str());
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
    EXPECT_EQ("mms://wms.sys.hinet.net/cts/Drama/09006251100.asf", parsed.str());
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
    EXPECT_EQ("nfs://server/path/to/file.txt", parsed.str());
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
    EXPECT_EQ("svn+ssh://svn.zope.org/repos/main/ZConfig/trunk/", parsed.str());
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
    EXPECT_EQ("git+ssh://git@github.com/user/project.git", parsed.str());
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
    EXPECT_EQ("http://www.python.org/doc/#frag", parsed.str());
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
    EXPECT_EQ("http://www.python.org:80/", parsed.str());
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
    EXPECT_EQ("http://www.python.org/", parsed.str());
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
    EXPECT_EQ("query?"     , Url::Url("http://foo.com/?query?"         ).query());
    EXPECT_EQ("repeats???q", Url::Url("http://foo.com/?repeats???q"    ).query());
    EXPECT_EQ(""           , Url::Url("http://foo.com/?????"           ).query());
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

TEST(RelativeTest, SchemeRelative)
{
    Url::Url base("http://foo.com/");
    EXPECT_EQ("http://relative.com/",
        Url::Url("//relative.com/").relative_to(base).str());
}

TEST(RelativeTest, IncludeUserinfo)
{
    Url::Url base("http://user@foo.com/");
    EXPECT_EQ("http://user@foo.com/path",
        Url::Url("/path").relative_to(base).str());
}

TEST(RelativeTest, AbsoluteRelative)
{
    Url::Url base("http://foo.com/");
    EXPECT_EQ("https://relative.com/",
        Url::Url("https://relative.com/").relative_to(base).str());
}

TEST(RelativeTest, RelativePath)
{
    Url::Url base("http://foo.com/a/b/c");
    EXPECT_EQ("http://foo.com/a/b/some/path",
        Url::Url("some/path").relative_to(base).str());
}

TEST(RelativeTest, RelativePathDirectory)
{
    Url::Url base("http://foo.com/a/b/c");
    EXPECT_EQ("http://foo.com/a/b/some/path/",
        Url::Url("some/path/").relative_to(base).str());
}

TEST(RelativeTest, AbsolutePath)
{
    Url::Url base("http://foo.com/a/b/c");
    EXPECT_EQ("http://foo.com/some/path",
        Url::Url("/some/path").relative_to(base).str());
}

TEST(RelativeTest, ParamsOnly)
{
    Url::Url base("http://foo.com/a/b/c;existing?query");
    EXPECT_EQ("http://foo.com/a/b/;params",
        Url::Url(";params").relative_to(base).str());
}

TEST(RelativeTest, PathAndParams)
{
    Url::Url base("http://foo.com/a/b/c");
    EXPECT_EQ("http://foo.com/a/b/path;params",
        Url::Url("path;params").relative_to(base).str());
}

TEST(RelativeTest, ParamsAndQuery)
{
    Url::Url base("http://foo.com/a/b/c");
    EXPECT_EQ("http://foo.com/a/b/;params?query",
        Url::Url(";params?query").relative_to(base).str());
}

TEST(RelativeTest, PathAndQuery)
{
    Url::Url base("http://foo.com/a/b/c");
    EXPECT_EQ("http://foo.com/a/b/path?query",
        Url::Url("path?query").relative_to(base).str());
}

TEST(RelativeTest, QueryOnly)
{
    Url::Url base("http://foo.com/a/b/c;params?existin");
    EXPECT_EQ("http://foo.com/a/b/c;params?query",
        Url::Url("?query").relative_to(base).str());
}

TEST(RelativeTest, PathAndFragment)
{
    Url::Url base("http://foo.com/a/b/c");
    EXPECT_EQ("http://foo.com/a/b/path#fragment",
        Url::Url("path#fragment").relative_to(base).str());
}

TEST(RelativeTest, FragmentOnly)
{
    Url::Url base("http://foo.com/a/b/c");
    EXPECT_EQ("http://foo.com/a/b/c#fragment",
        Url::Url("#fragment").relative_to(base).str());
}

TEST(RelativeTest, Dot)
{
    Url::Url base("http://foo.com/a/b/c/d");
    EXPECT_EQ("http://foo.com/a/b/c/",
        Url::Url(".").relative_to(base).abspath().str());
}

TEST(RelativeTest, DotDirectoryBase)
{
    Url::Url base("http://foo.com/a/b/c/d/");
    EXPECT_EQ("http://foo.com/a/b/c/d/",
        Url::Url(".").relative_to(base).abspath().str());
}

TEST(RelativeTest, DotSlash)
{
    Url::Url base("http://foo.com/a/b/c/d");
    EXPECT_EQ("http://foo.com/a/b/c/",
        Url::Url("./").relative_to(base).abspath().str());
}

TEST(RelativeTest, DotDot)
{
    Url::Url base("http://foo.com/a/b/c/d");
    EXPECT_EQ("http://foo.com/a/b/",
        Url::Url("..").relative_to(base).abspath().str());
}

TEST(RelativeTest, DotDotDirectoryBase)
{
    Url::Url base("http://foo.com/a/b/c/d/");
    EXPECT_EQ("http://foo.com/a/b/c/",
        Url::Url("..").relative_to(base).abspath().str());
}

TEST(RelativeTest, DotDotSlash)
{
    Url::Url base("http://foo.com/a/b/c/d");
    EXPECT_EQ("http://foo.com/a/b/",
        Url::Url("../").relative_to(base).abspath().str());
}

TEST(RelativeTest, DotDotSlashName)
{
    Url::Url base("http://foo.com/a/b/c/d");
    EXPECT_EQ("http://foo.com/a/b/g",
        Url::Url("../g").relative_to(base).abspath().str());
}

TEST(RelativeTest, Grandparent)
{
    Url::Url base("http://foo.com/a/b/c/d");
    EXPECT_EQ("http://foo.com/a/",
        Url::Url("../..").relative_to(base).abspath().str());
}

TEST(RelativeTest, GrandparentDirectory)
{
    Url::Url base("http://foo.com/a/b/c/d");
    EXPECT_EQ("http://foo.com/a/",
        Url::Url("../../").relative_to(base).abspath().str());
}

TEST(RelativeTest, EmptyBase)
{
    Url::Url base("");
    EXPECT_EQ("http://foo.com/a;param?query#fragment",
        Url::Url("http://foo.com/a;param?query#fragment").relative_to(base).abspath().str());
}

TEST(RelativeTest, EmptyRelative)
{
    Url::Url base("http://foo.com/a/b/c;params?query#fragment");
    EXPECT_EQ("http://foo.com/a/b/c;params?query#fragment",
        Url::Url("").relative_to(base).str());
}

TEST(RelativeTest, EmptyBasePath)
{
    Url::Url base("http://foo.com");
    EXPECT_EQ("http://foo.com/path",
        Url::Url("path").relative_to(base).str());
}

TEST(RelativeTest, EmptyRelativePath)
{
    Url::Url base("http://foo.com/path");
    EXPECT_EQ("http://relative.com/",
        Url::Url("http://relative.com").relative_to(base).str());
}

TEST(RelativeTest, RelativeBase)
{
    Url::Url base("base");
    EXPECT_EQ("relative",
        Url::Url("relative").relative_to(base).str());
}

TEST(RelativeTest, RelativeBaseWithSegments)
{
    Url::Url base("base/path");
    EXPECT_EQ("base/relative/path",
        Url::Url("relative/path").relative_to(base).str());
}

TEST(RelativeTest, BaseWithDirectory)
{
    Url::Url base("http://foo.com/path/is/directory/");
    EXPECT_EQ("http://foo.com/path/is/directory/relative",
        Url::Url("relative").relative_to(base).str());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
