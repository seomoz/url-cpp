#ifndef URL_CPP_H
#define URL_CPP_H

#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace Url
{

    struct UrlParseException : public std::logic_error
    {
        UrlParseException(const std::string& message) : std::logic_error(message) {}
    };

    struct Url
    {
        /* Character classes */
        const static std::string GEN_DELIMS;
        const static std::string SUB_DELIMS;
        const static std::string ALPHA;
        const static std::string DIGIT;
        const static std::string UNRESERVED;
        const static std::string RESERVED;
        const static std::string PCHAR;
        const static std::string PATH;
        const static std::string QUERY;
        const static std::string FRAGMENT;
        const static std::string USERINFO;
        const static std::string HEX;
        const static std::string SCHEME;

        explicit Url(const std::string& url);

        Url(const Url& other)
            : scheme_(other.scheme_)
            , host_(other.host_)
            , port_(other.port_)
            , path_(other.path_)
            , params_(other.params_)
            , query_(other.query_)
            , fragment_(other.fragment_)
            , userinfo_(other.userinfo_) { }

        /**************************
         * Component-wise access. *
         **************************/
        const std::string& scheme() const { return scheme_; }

        const std::string& host() const { return host_; }

        const int port() const { return port_; }

        const std::string& path() const { return path_; }

        const std::string& params() const { return params_; }

        const std::string& query() const { return query_; }

        const std::string& fragment() const { return fragment_; }

        const std::string& userinfo() const { return userinfo_; }

        /**
         * Get a new string representation of the URL.
         **/
        std::string str() const;

        /*********************
         * Chainable methods *
         *********************/

        /**
         * Make the path absolute.
         *
         * Evaluate '.', '..', and excessive slashes.
         */
        Url& abspath();

        /**
         * Evaluate this URL relative fo `other`, placing the result in this object.
         */
        Url& relative_to(const std::string& other)
        {
            return relative_to(Url(other));
        }

        /**
         * Evaluate this URL relative fo `other`, placing the result in this object.
         */
        Url& relative_to(const Url& other);

    private:
        // Private, unimplemented to prevent use.
        Url();

        /**
         * Remove repeated, leading, and trailing instances of chr from the string.
         */
        void remove_repeats(std::string& str, const char chr);

        std::string scheme_;
        std::string host_;
        int port_;
        std::string path_;
        std::string params_;
        std::string query_;
        std::string fragment_;
        std::string userinfo_;
    };

}

#endif
