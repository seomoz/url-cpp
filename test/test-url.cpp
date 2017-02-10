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

TEST(ParseTest, DoesNotUseNetloc)
{
    Url::Url parsed("javascript:console.log('hello')");
    EXPECT_EQ("javascript", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("console.log('hello')", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
    EXPECT_EQ("javascript:console.log('hello')", parsed.str());
}

TEST(ParseTest, DoesNotUseParams)
{
    Url::Url parsed("javascript:console.log('hello');console.log('world')");
    EXPECT_EQ("javascript", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("console.log('hello');console.log('world')", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
    EXPECT_EQ("javascript:console.log('hello');console.log('world')", parsed.str());
}

TEST(ParseTest, EmptyQuery)
{
    Url::Url parsed("http://example.com/?");
    EXPECT_EQ("http", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("example.com", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("/", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
    EXPECT_EQ("http://example.com/?", parsed.str());
}

TEST(ParseTest, EmptyParams)
{
    Url::Url parsed("http://example.com/;");
    EXPECT_EQ("http", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("example.com", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("/", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
    EXPECT_EQ("http://example.com/;", parsed.str());
}

TEST(ParseTest, TelProtocol)
{
    Url::Url parsed("tel:0108202201");
    EXPECT_EQ("tel", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("0108202201", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
    EXPECT_EQ("tel:0108202201", parsed.str());
}

TEST(ParseTest, UnknownProtocol)
{
    Url::Url parsed("unknown:0108202201");
    EXPECT_EQ("", parsed.scheme());
    EXPECT_EQ("", parsed.userinfo());
    EXPECT_EQ("", parsed.host());
    EXPECT_EQ(0, parsed.port());
    EXPECT_EQ("unknown:0108202201", parsed.path());
    EXPECT_EQ("", parsed.params());
    EXPECT_EQ("", parsed.query());
    EXPECT_EQ("", parsed.fragment());
    EXPECT_EQ("unknown:0108202201", parsed.str());
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

TEST(ParseTest, TestPortInvalid)
{
    ASSERT_THROW(Url::Url("http://:::cnn.com/"), Url::UrlParseException);
}

TEST(AssignTest, AssignsValue)
{
    Url::Url assignee("");
    Url::Url parsed("http://user@example.com:8080/path;param?query#fragment");
    assignee.assign(parsed);
    EXPECT_EQ(assignee.scheme(), parsed.scheme());
    EXPECT_EQ(assignee.userinfo(), parsed.userinfo());
    EXPECT_EQ(assignee.host(), parsed.host());
    EXPECT_EQ(assignee.port(), parsed.port());
    EXPECT_EQ(assignee.path(), parsed.path());
    EXPECT_EQ(assignee.params(), parsed.params());
    EXPECT_EQ(assignee.query(), parsed.query());
    EXPECT_EQ(assignee.fragment(), parsed.fragment());
}

TEST(EqualityTest, RequiresSchemeEquality)
{
    Url::Url a("http://user@example.com:8080/path;param?query#fragment");
    Url::Url b(a);
    EXPECT_EQ(a, b);
    b.setScheme("https");
    EXPECT_NE(a, b);
}

TEST(EqualityTest, RequiresUserinfoEquality)
{
    Url::Url a("http://user@example.com:8080/path;param?query#fragment");
    Url::Url b(a);
    EXPECT_EQ(a, b);
    b.setUserinfo("name");
    EXPECT_NE(a, b);
}

TEST(EqualityTest, RequiresHostEquality)
{
    Url::Url a("http://user@example.com:8080/path;param?query#fragment");
    Url::Url b(a);
    EXPECT_EQ(a, b);
    b.setHost("new.host");
    EXPECT_NE(a, b);
}

TEST(EqualityTest, RequiresPortEquality)
{
    Url::Url a("http://user@example.com:8080/path;param?query#fragment");
    Url::Url b(a);
    EXPECT_EQ(a, b);
    b.setPort(1234);
    EXPECT_NE(a, b);
}

TEST(EqualityTest, RequiresPathEquality)
{
    Url::Url a("http://user@example.com:8080/path;param?query#fragment");
    Url::Url b(a);
    EXPECT_EQ(a, b);
    b.setPath("/new/path");
    EXPECT_NE(a, b);
}

TEST(EqualityTest, RequiresParamsEquality)
{
    Url::Url a("http://user@example.com:8080/path;param?query#fragment");
    Url::Url b(a);
    EXPECT_EQ(a, b);
    b.setParams("new;params");
    EXPECT_NE(a, b);
}

TEST(EqualityTest, RequiresQueryEquality)
{
    Url::Url a("http://user@example.com:8080/path;param?query#fragment");
    Url::Url b(a);
    EXPECT_EQ(a, b);
    b.setQuery("new=query");
    EXPECT_NE(a, b);
}

TEST(EqualityTest, RequiresFragmentEquality)
{
    Url::Url a("http://user@example.com:8080/path;param?query#fragment");
    Url::Url b(a);
    EXPECT_EQ(a, b);
    b.setFragment("new-fragment");
    EXPECT_NE(a, b);
}

TEST(EquivTest, HttpPort)
{
    Url::Url a("http://foo.com:80");
    Url::Url b("http://foo.com/");
    EXPECT_TRUE(a.equiv(b));
    EXPECT_TRUE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(EquivTest, HttpsPort)
{
    Url::Url a("https://foo.com:443");
    Url::Url b("https://foo.com/");
    EXPECT_TRUE(a.equiv(b));
    EXPECT_TRUE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(EquivTest, QueryOrder)
{
    Url::Url a("http://foo.com/?b=2&&&&a=1");
    Url::Url b("http://foo.com/?a=1&b=2");
    EXPECT_TRUE(a.equiv(b));
    EXPECT_TRUE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(EquivTest, EscapeCodeCasing)
{
    Url::Url a("http://foo.com/%A2%B3");
    Url::Url b("http://foo.com/%a2%b3");
    EXPECT_TRUE(a.equiv(b));
    EXPECT_TRUE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(EquivTest, RelativePath)
{
    Url::Url a("http://foo.com/a/../b/.");
    Url::Url b("http://foo.com/b/");
    EXPECT_TRUE(a.equiv(b));
    EXPECT_TRUE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(EquivTest, PunycodingLower)
{
    Url::Url a("http://www.k\xc3\xbcndigen.de/");
    Url::Url b("http://www.xn--kndigen-n2a.de/");
    EXPECT_TRUE(a.equiv(b));
    EXPECT_TRUE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(EquivTest, PunycodingUpper)
{
    Url::Url a("http://www.k\xc3\xbcndiGen.DE/");
    Url::Url b("http://www.xn--kndigen-n2a.de/");
    EXPECT_TRUE(a.equiv(b));
    EXPECT_TRUE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(EquivTest, Userinfo)
{
    Url::Url a("http://user:pass@foo.com/");
    Url::Url b("http://foo.com/");
    EXPECT_TRUE(a.equiv(b));
    EXPECT_TRUE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(NotEquivTest, HostnameMismatch)
{
    Url::Url a("http://foo.com:");
    Url::Url b("http://foo.co.uk/");
    EXPECT_FALSE(a.equiv(b));
    EXPECT_FALSE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(NotEquivTest, DifferentNonDefaultHttpPort)
{
    Url::Url a("http://foo.com:8080");
    Url::Url b("http://foo.com/");
    EXPECT_FALSE(a.equiv(b));
    EXPECT_FALSE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(NotEquivTest, DifferentNonDefaultHttpsPort)
{
    Url::Url a("https://foo.com:4430");
    Url::Url b("https://foo.com/");
    EXPECT_FALSE(a.equiv(b));
    EXPECT_FALSE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(NotEquivTest, DifferentQueries)
{
    Url::Url a("http://foo.com?page&foo");
    Url::Url b("http://foo.com/?page");
    EXPECT_FALSE(a.equiv(b));
    EXPECT_FALSE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(NotEquivTest, AdditionalQueries)
{
    Url::Url a("http://foo.com/?b=2&c&a=1");
    Url::Url b("http://foo.com/?a=1&b=2");
    EXPECT_FALSE(a.equiv(b));
    EXPECT_FALSE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(NotEquivTest, DifferentEscapeSequences)
{
    Url::Url a("http://foo.com/%A2%B3%C3");
    Url::Url b("http://foo.com/%a2%b3");
    EXPECT_FALSE(a.equiv(b));
    EXPECT_FALSE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(NotEquivTest, DifferentHosts)
{
    Url::Url a("http://www.kündïgen.de/");
    Url::Url b("http://www.xn--kndigen-n2a.de/");
    EXPECT_FALSE(a.equiv(b));
    EXPECT_FALSE(b.equiv(a));
    EXPECT_NE(a, b);
}

TEST(SetAttributesTest, Scheme)
{
    EXPECT_EQ("https://host.name/",
        Url::Url("http://host.name/").setScheme("https").str());
}

TEST(SetAttributesTest, Userinfo)
{
    EXPECT_EQ("http://name@host.name/",
        Url::Url("http://user@host.name/").setUserinfo("name").str());
}

TEST(SetAttributesTest, Host)
{
    EXPECT_EQ("http://new.host/",
        Url::Url("http://old.host/").setHost("new.host").str());
}

TEST(SetAttributesTest, Port)
{
    EXPECT_EQ("http://host.name:8080/",
        Url::Url("http://host.name/").setPort(8080).str());
}

TEST(SetAttributesTest, Path)
{
    EXPECT_EQ("http://host.name/new/path",
        Url::Url("http://host.name/old/path").setPath("/new/path").str());
}

TEST(SetAttributesTest, Params)
{
    EXPECT_EQ("http://host.name/;new;params",
        Url::Url("http://host.name/;old;params").setParams("new;params").str());
}

TEST(SetAttributesTest, Query)
{
    EXPECT_EQ("http://host.name/?new=query",
        Url::Url("http://host.name/?old=query").setQuery("new=query").str());
}

TEST(SetAttributesTest, Fragment)
{
    EXPECT_EQ("http://host.name/#new-fragment",
        Url::Url("http://host.name/#old-fragment").setFragment("new-fragment").str());
}

TEST(HostnameTest, LowercasesHostname)
{
    EXPECT_EQ("www.testing.com", Url::Url("http://www.TESTING.coM").host());
    EXPECT_EQ("www.testing.com", Url::Url("http://WWW.testing.com").host());
    EXPECT_EQ("www.testing.com", Url::Url("http://www.testing.com/FOO").host());
}

TEST(QueryTest, SanitizesQuery)
{
    EXPECT_EQ("a=1&b=2"    , Url::Url("http://foo.com/?a=1&&&&&&b=2"   ).strip().query());
    EXPECT_EQ("foo=2"      , Url::Url("http://foo.com/????foo=2"       ).strip().query());
    EXPECT_EQ("foo=2"      , Url::Url("http://foo.com/?foo=2&&&"       ).strip().query());
    EXPECT_EQ("query?"     , Url::Url("http://foo.com/?query?"         ).strip().query());
    EXPECT_EQ("repeats???q", Url::Url("http://foo.com/?repeats???q"    ).strip().query());
    EXPECT_EQ(""           , Url::Url("http://foo.com/?????"           ).strip().query());
}

TEST(ParamTest, SanitizesParams)
{
    EXPECT_EQ(""           , Url::Url("http://foo.com/"                ).strip().params());
    EXPECT_EQ("a=1;b=2"    , Url::Url("http://foo.com/;a=1;;;;;;b=2"   ).strip().params());
    EXPECT_EQ("a=1;b=2"    , Url::Url("http://foo.com/;;;a=1;;;;;;b=2" ).strip().params());
    EXPECT_EQ("a=1;b=2"    , Url::Url("http://foo.com/;a=1;;;;;;b=2;;;").strip().params());
}

TEST(AbspathTest, BasicPath)
{
    std::string example("http://foo.com/howdy");
    EXPECT_EQ("/howdy",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/howdy",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, RepeatedSeparator)
{
    std::string example("http://foo.com/hello//how//are");
    EXPECT_EQ("/hello/how/are",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/hello/how/are",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, ParentDirectory)
{
    std::string example("http://foo.com/hello/../how/are");
    EXPECT_EQ("/how/are",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/how/are",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, ParentDirectoryWithRepeatedSeparators)
{
    std::string example("http://foo.com/hello//..//how/");
    EXPECT_EQ("/how/",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/how/",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, GrandparentDirectory)
{
    std::string example("http://foo.com/a/b/../../c");
    EXPECT_EQ("/c",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/c",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, UpMoreLevelsThanSegments)
{
    std::string example("http://foo.com/../../../c");
    EXPECT_EQ("c",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/c",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, CurrentDirectory)
{
    std::string example("http://foo.com/./hello");
    EXPECT_EQ("/hello",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/hello",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, CurrentDirectoryRepeated)
{
    std::string example("http://foo.com/./././hello");
    EXPECT_EQ("/hello",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/hello",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, MultipleSegmentsDirectory)
{
    std::string example("http://foo.com/a/b/c/");
    EXPECT_EQ("/a/b/c/",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/a/b/c/",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, TrailingParentDirectory)
{
    std::string example("http://foo.com/a/b/c/..");
    EXPECT_EQ("/a/b/",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/a/b/",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, TrailingCurrentDirectory)
{
    std::string example("http://foo.com/a/b/.");
    EXPECT_EQ("/a/b/",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/a/b/",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, TrailingCurrentDirectoryMultiple)
{
    std::string example("http://foo.com/a/b/./././");
    EXPECT_EQ("/a/b/",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/a/b/",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, TrailingParentDirectorySlash)
{
    std::string example("http://foo.com/a/b/../");
    EXPECT_EQ("/a/",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/a/",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, OnlyCurrentDirectory)
{
    std::string example("http://foo.com/.");
    EXPECT_EQ("/",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, OnlyMultipleParentDirectories)
{
    std::string example("http://foo.com/../../..");
    EXPECT_EQ("/",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, TrailingDotInLastSegment)
{
    std::string example("http://foo.com//foo/../whiz.");
    EXPECT_EQ("/whiz.",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/whiz.",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, TrailingDotInSegmentSlash)
{
    std::string example("http://foo.com//foo/whiz./");
    EXPECT_EQ("/foo/whiz./",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/foo/whiz./",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, TrailingDotInSegment)
{
    std::string example("http://foo.com//foo/whiz./bar");
    EXPECT_EQ("/foo/whiz./bar",
        Url::Url(example).abspath().path());
    EXPECT_EQ("http://foo.com/foo/whiz./bar",
        Url::Url(example).abspath().str());
}

TEST(AbspathTest, DoesNotUseNetloc)
{
    std::string example("javascript:console.log('hello')");
    EXPECT_EQ("console.log('hello')",
        Url::Url(example).abspath().path());
    EXPECT_EQ("javascript:console.log('hello')",
        Url::Url(example).abspath().str());
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

TEST(RelativeTest, RelativeSchemeDoesntUseRelative)
{
    Url::Url base("http://foo.com/path");
    EXPECT_EQ("javascript:console.log(\"hello\")",
        Url::Url("javascript:console.log(\"hello\")").relative_to(base).str());
}

TEST(RelativeTest, BaseSchemeDoesntUseRelative)
{
    Url::Url base("javascript:console.log(\"hello\")");
    EXPECT_EQ("http://foo.com/path",
        Url::Url("http://foo.com/path").relative_to(base).str());
}

TEST(EscapeTest, IncompleteEntity)
{
    EXPECT_EQ("trailing-incomplete%252",
        Url::Url("trailing-incomplete%2").escape().str());
}

TEST(EscapeTest, ZeroLengthEntity)
{
    EXPECT_EQ("zero-length-%25",
        Url::Url("zero-length-%").escape().str());
}

TEST(EscapeTest, NonHexEntity)
{
    EXPECT_EQ("non-hex-%25ZW",
        Url::Url("non-hex-%ZW").escape().str());
}

TEST(EscapeTest, ExtraDigitsInEntity)
{
    EXPECT_EQ("more-digits%20AF",
        Url::Url("more-digits%20AF").escape().str());
}

TEST(EscapeTest, CapitalizeEntities)
{
    EXPECT_EQ("capitalize-entities%5E",
        Url::Url("capitalize-entities%5e").escape().str());
}

TEST(EscapeTest, HighEntities)
{
    EXPECT_EQ("high-entities%EF",
        Url::Url("high-entities%EF").escape().str());
}

TEST(EscapeTest, PreservesSpaces)
{
    EXPECT_EQ("hello%20and%20how%20are%20you",
        Url::Url("hello%20and%20how%20are%20you").escape().str());
}

TEST(EscapeTest, EscapesSpaces)
{
    EXPECT_EQ("hello%20world",
        Url::Url("hello world").escape().str());
}

TEST(EscapeTest, PermissivePreservesSafeEntities)
{
    EXPECT_EQ("path's-ok",
        Url::Url("path's-ok").escape().str());
}

TEST(EscapeTest, StrictPreservesSafeEntities)
{
    EXPECT_EQ("path's-ok",
        Url::Url("path's-ok").escape(true).str());
}

TEST(EscapeTest, PermissiveUnescapesSafeEntities)
{
    EXPECT_EQ("path's-ok",
        Url::Url("path%27s-ok").escape().str());
}

TEST(EscapeTest, StrictPreservesSafeButReservedEntities)
{
    EXPECT_EQ("path%27s-ok",
        Url::Url("path%27s-ok").escape(true).str());
}

TEST(EscapeTest, PreservesHasQuery)
{
    EXPECT_EQ("/path?", Url::Url("/path?").escape(true).str());
}

TEST(EscapeTest, PreservesHasParams)
{
    EXPECT_EQ("/path;", Url::Url("/path;").escape(true).str());
}

TEST(EscapeTest, PermissiveFromUrlPy)
{
    EXPECT_EQ("danny\'s%20pub",
        Url::Url("danny\'s pub").escape().str());
    EXPECT_EQ("danny\'s%20pub",
        Url::Url("danny%27s pub").escape().str());
    EXPECT_EQ("danny\'s%20pub?foo=bar&yo",
        Url::Url("danny\'s pub?foo=bar&yo").escape().str());
    EXPECT_EQ("hello,%20world",
        Url::Url("hello%2c world").escape().str());
    EXPECT_EQ("%3F%23%5B%5D",
        Url::Url("%3f%23%5b%5d").escape().str());
    // Thanks to @myronmarston for these test cases
    EXPECT_EQ("foo?bar%20none=foo%20bar",
        Url::Url("foo?bar none=foo bar").escape().str());
    EXPECT_EQ("foo;a=1;b=2?a=1&b=2",
        Url::Url("foo;a=1;b=2?a=1&b=2").escape().str());
    EXPECT_EQ("foo?bar=%5B%22hello%22,%22howdy%22%5D",
        Url::Url("foo?bar=[\"hello\",\"howdy\"]").escape().str());
    // Example from the wild
    EXPECT_EQ("http://www.balset.com/DE3FJ4Yg/p:h=300&m=2011~07~25~2444705.png&ma=cb&or=1&w=400/2011/10/10/2923710.jpg",
        Url::Url("http://www.balset.com/DE3FJ4Yg/p:h=300&m=2011~07~25~2444705.png&ma=cb&or=1&w=400/2011/10/10/2923710.jpg").escape().str());
    // Example with userinfo
    EXPECT_EQ("http://user:pass@foo.com/",
        Url::Url("http://user%3Apass@foo.com/").escape().str());
}

TEST(EscapeTest, StrictFromUrlPy)
{
    EXPECT_EQ("danny%27s%20pub",
        Url::Url("danny%27s pub").escape(true).str());
    EXPECT_EQ("this_and_that",
        Url::Url("this%5Fand%5Fthat").escape(true).str());
    EXPECT_EQ("http://user:pass@foo.com/",
        Url::Url("http://user:pass@foo.com").escape(true).str());
    EXPECT_EQ("http://Jos%C3%A9:no%20way@foo.com/",
        Url::Url("http://José:no way@foo.com").escape(true).str());
    EXPECT_EQ("http://oops!:don%27t@foo.com/",
        Url::Url("http://oops!:don%27t@foo.com").escape(true).str());
    EXPECT_EQ("espa%C3%B1ola,nm%2Cusa.html?gunk=junk+glunk&foo=bar%20baz",
        Url::Url("española,nm%2cusa.html?gunk=junk+glunk&foo=bar baz").escape(true).str());
    EXPECT_EQ("http://foo.com/bar%0Abaz.html%0A",
        Url::Url("http://foo.com/bar\nbaz.html\n").escape(true).str());
    EXPECT_EQ("http://foo.com/bar.jsp?param=%0A/value%2F",
        Url::Url("http://foo.com/bar.jsp?param=\n/value%2F").escape(true).str());
    EXPECT_EQ("http://user%3Apass@foo.com/",
        Url::Url("http://user%3apass@foo.com/").escape(true).str());
}

TEST(UnescapeTest, KeepUnescaped)
{
    EXPECT_EQ("this's a test",
        Url::Url("this's%20a%20test").unescape().str());
}

TEST(UnescapeTest, IncompleteEntity)
{
    EXPECT_EQ("incomplete entity %2",
        Url::Url("incomplete%20entity%20%2").unescape().str());
}

TEST(UnescapeTest, NonHexEntity)
{
    EXPECT_EQ("a non hex %gh entity",
        Url::Url("a%20non%20hex%20%gh%20entity").unescape().str());
}

TEST(UnescapeTest, PreservesHasQuery)
{
    EXPECT_EQ("/path?", Url::Url("/path?").unescape().str());
}

TEST(UnescapeTest, PreservesHasParams)
{
    EXPECT_EQ("/path;", Url::Url("/path;").unescape().str());
}

TEST(UnescapeTest, UnescapesEverything)
{
    std::string escaped =
        "http://hei%C3%9Fe@domain.com/s%C3%B8me%3Bw%C3%A9ird%3Fex%C3%A5mple";
    std::string unescaped =
        "http://hei\xc3\x9f" "e@domain.com/s\xc3\xb8me;w\xc3\xa9ird?ex\xc3\xa5mple";
    EXPECT_EQ(unescaped, Url::Url(escaped).unescape().str());
}

TEST(FilterParams, FiltersQuery)
{
    std::unordered_set<std::string> blacklist = {"c"};
    EXPECT_EQ("?a=1&b=2&d=4", Url::Url("?a=1&b=2&c=3&d=4").deparam(blacklist).str());
    EXPECT_EQ("?prefix_c=2", Url::Url("?prefix_c=2").deparam(blacklist).str());
    EXPECT_EQ("", Url::Url("?c=2").deparam(blacklist).str());
}

TEST(FilterParams, FiltersParams)
{
    std::unordered_set<std::string> blacklist = {"c"};
    EXPECT_EQ(";a=1;b=2;d=4", Url::Url(";a=1;b=2;c=3;d=4").deparam(blacklist).str());
    EXPECT_EQ(";prefix_c=2", Url::Url(";prefix_c=2").deparam(blacklist).str());
    EXPECT_EQ("", Url::Url(";c=2").deparam(blacklist).str());
}

TEST(FilterParams, CaseInsensitivity)
{
    std::unordered_set<std::string> blacklist = {"hello"};
    EXPECT_EQ("", Url::Url("?hELLo=2").deparam(blacklist).str());
    EXPECT_EQ("", Url::Url("?HELLo=2").deparam(blacklist).str());
}

TEST(FilterParams, RemovesEmptyQuery)
{
    std::unordered_set<std::string> blacklist = {"hello"};
    EXPECT_EQ("/path", Url::Url("/path?").deparam(blacklist).str());
}

TEST(FilterParams, RemovesEmptyParams)
{
    std::unordered_set<std::string> blacklist = {"hello"};
    EXPECT_EQ("/path", Url::Url("/path;").deparam(blacklist).str());
}

TEST(FilterParams, PredicateFormQuery)
{
    auto predicate = [](std::string& name, std::string& value)
    {
        // Remove parameters with the value 2 or with "foo" in the name
        return (value == "2") || (name.find("foo") != std::string::npos);
    };
    EXPECT_EQ("?a=1&c=3",
        Url::Url("?a=1&b=2&c=3&not-foo&yes-foo=18").deparam(predicate).str());
}

TEST(FilterParams, PredicateFormParams)
{
    auto predicate = [](std::string& name, std::string& value)
    {
        // Remove parameters with the value 2 or with "foo" in the name
        return (value == "2") || (name.find("foo") != std::string::npos);
    };
    EXPECT_EQ(";a=1;c=3",
        Url::Url(";a=1;b=2;c=3;not-foo;yes-foo=18").deparam(predicate).str());
}

TEST(SortQueryTest, SortsQueries)
{
    EXPECT_EQ("http://foo.com/?a=1&b=2&c=3",
        Url::Url("http://foo.com/?b=2&c=3&a=1").sort_query().str());
}

TEST(SortQueryTest, SortsParams)
{
    EXPECT_EQ("http://foo.com/;a=1;b=2;c=3",
        Url::Url("http://foo.com/;b=2;c=3;a=1").sort_query().str());
}

TEST(SortQueryTest, Empty)
{
    EXPECT_EQ("http://foo.com/",
        Url::Url("http://foo.com/").sort_query().str());
}

TEST(SortQueryTest, SingleQuery)
{
    EXPECT_EQ("http://foo.com/?a=7",
        Url::Url("http://foo.com/?a=7").sort_query().str());
}

TEST(SortQueryTest, SingleParam)
{
    EXPECT_EQ("http://foo.com/;a=7",
        Url::Url("http://foo.com/;a=7").sort_query().str());
}

TEST(RemoveDefaultPortTest, HttpTest)
{
    EXPECT_EQ("http://foo.com/",
        Url::Url("http://foo.com:80/").remove_default_port().str());
}

TEST(RemoveDefaultPortTest, HttpsTest)
{
    EXPECT_EQ("https://foo.com/",
        Url::Url("https://foo.com:443/").remove_default_port().str());
}

TEST(RemoveDefaultPortTest, Http8080Test)
{
    EXPECT_EQ("http://foo.com:8080/",
        Url::Url("http://foo.com:8080/").remove_default_port().str());
}

TEST(DeuserinfoTest, Deuserinfo)
{
    EXPECT_EQ("http://foo.com/",
        Url::Url("http://user:pass@foo.com/").deuserinfo().str());
    EXPECT_EQ("http://foo.com/",
        Url::Url("http://just-user@foo.com/").deuserinfo().str());
}

TEST(DefragTest, Defrag)
{
    EXPECT_EQ("http://foo.com/path",
        Url::Url("http://foo.com/path#fragment").defrag().str());
}

TEST(FullpathTest, OnlyPath)
{
    EXPECT_EQ("/path", Url::Url("path").fullpath());
}

TEST(FullpathTest, LeadingSlashPath)
{
    EXPECT_EQ("/path", Url::Url("/path").fullpath());
}

TEST(FullpathTest, EmptyPath)
{
    EXPECT_EQ("/", Url::Url("").fullpath());
}

TEST(FullpathTest, Params)
{
    EXPECT_EQ("/;params",
        Url::Url(";params").fullpath());
}

TEST(FullpathTest, Query)
{
    EXPECT_EQ("/?query",
        Url::Url("?query").fullpath());
}

TEST(FullpathTest, Fragment)
{
    EXPECT_EQ("/#fragment",
        Url::Url("#fragment").fullpath());
}

TEST(FullpathTest, ParamsAndFriends)
{
    EXPECT_EQ("/path;params?query#fragment",
        Url::Url("/path;params?query#fragment").fullpath());
}

TEST(FullpathTest, EmptyQuery)
{
    EXPECT_EQ("/?", Url::Url("?").fullpath());
}

TEST(FullpathTest, EmptyParams)
{
    EXPECT_EQ("/;", Url::Url(";").fullpath());
}

TEST(HostReversedTest, Basic)
{
    EXPECT_EQ("http://com.example/path",
        Url::Url("http://example.com/path").host_reversed().str());
}

TEST(HostReversedTest, Empty)
{
    EXPECT_EQ("/path",
        Url::Url("/path").host_reversed().str());
}

TEST(HostReversedTest, Reversible)
{
    EXPECT_EQ("http://example.com/path",
        Url::Url("http://example.com/path").host_reversed().host_reversed().str());
}

TEST(PunycodeTest, German)
{
    std::string unencoded("http://www.kündigen.de/");
    std::string encoded("http://www.xn--kndigen-n2a.de/");
    EXPECT_EQ(encoded, Url::Url(unencoded).punycode().str());
    EXPECT_EQ(unencoded, Url::Url(encoded).unpunycode().str());
    EXPECT_EQ(encoded, Url::Url(encoded).unpunycode().punycode().str());
    EXPECT_EQ(unencoded, Url::Url(unencoded).punycode().unpunycode().str());
}

TEST(PunycodeTest, Russian)
{
    std::string unencoded("http://россия.иком.museum/");
    std::string encoded("http://xn--h1alffa9f.xn--h1aegh.museum/");
    EXPECT_EQ(encoded, Url::Url(unencoded).punycode().str());
    EXPECT_EQ(unencoded, Url::Url(encoded).unpunycode().str());
    EXPECT_EQ(encoded, Url::Url(encoded).unpunycode().punycode().str());
    EXPECT_EQ(unencoded, Url::Url(unencoded).punycode().unpunycode().str());
}

TEST(PunycodeTest, SingleSegment)
{
    std::string unencoded("http://bücher/");
    std::string encoded("http://xn--bcher-kva/");
    EXPECT_EQ(encoded, Url::Url(unencoded).punycode().str());
    EXPECT_EQ(unencoded, Url::Url(encoded).unpunycode().str());
    EXPECT_EQ(encoded, Url::Url(encoded).unpunycode().punycode().str());
    EXPECT_EQ(unencoded, Url::Url(unencoded).punycode().unpunycode().str());
}

TEST(PunycodeTest, RelativeTest)
{
    std::string unencoded("relative-url");
    std::string encoded("relative-url");
    EXPECT_EQ(encoded, Url::Url(unencoded).punycode().str());
    EXPECT_EQ(unencoded, Url::Url(encoded).unpunycode().str());
    EXPECT_EQ(encoded, Url::Url(encoded).unpunycode().punycode().str());
    EXPECT_EQ(unencoded, Url::Url(unencoded).punycode().unpunycode().str());
}

TEST(PunycodeTest, Safe)
{
    std::string unencoded("http://safe.segments/");
    std::string encoded("http://safe.segments/");
    EXPECT_EQ(encoded, Url::Url(unencoded).punycode().str());
}

TEST(PunycodeTest, SingleDot)
{
    ASSERT_THROW(Url::Url("http://./").punycode(), std::invalid_argument);
}

TEST(PunycodeTest, EmptySegment)
{
    ASSERT_THROW(Url::Url("http://foo..com/").punycode(), std::invalid_argument);
}

TEST(PunycodeTest, TrailingEmptySegment)
{
    ASSERT_THROW(Url::Url("http://foo../").punycode(), std::invalid_argument);
}

TEST(PunycodeTest, TrailingPeriod)
{
    std::string unencoded("http://foo.com./");
    std::string encoded("http://foo.com/");
    EXPECT_EQ(encoded, Url::Url(unencoded).punycode().str());
}

TEST(PunycodeTest, SegmentTooLong)
{
    std::string unencoded(
        "http://this-is-a-very-long-segment-that-has-more-than-sixty-three-characters.com/");
    ASSERT_THROW(Url::Url(unencoded).punycode(), std::invalid_argument);
}

TEST(PunycodeTest, TrailingSegmentTooLong)
{
    std::string unencoded(
        "http://this-is-a-very-long-segment-that-has-more-than-sixty-three-characters/");
    ASSERT_THROW(Url::Url(unencoded).punycode(), std::invalid_argument);
}
