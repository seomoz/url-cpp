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

    struct CharacterClass
    {
        CharacterClass(const std::string& chars) : chars_(chars), map_(256, false)
        {
            for (auto it = chars_.begin(); it != chars_.end(); ++it)
            {
                map_[static_cast<size_t>(*it)] = true;
            }
        }

        bool operator()(char c) const
        {
            return map_[static_cast<unsigned char>(c)];
        }

        const std::string& chars() const
        {
            return chars_;
        }

    private:
        // Private, unimplemented to prevent use
        CharacterClass();
        CharacterClass(const CharacterClass& other);

        std::string chars_;
        std::vector<bool> map_;
    };

    struct Url
    {
        /* Character classes */
        const static CharacterClass GEN_DELIMS;
        const static CharacterClass SUB_DELIMS;
        const static CharacterClass ALPHA;
        const static CharacterClass DIGIT;
        const static CharacterClass UNRESERVED;
        const static CharacterClass RESERVED;
        const static CharacterClass PCHAR;
        const static CharacterClass PATH;
        const static CharacterClass QUERY;
        const static CharacterClass FRAGMENT;
        const static CharacterClass USERINFO;
        const static CharacterClass HEX;
        const static CharacterClass SCHEME;
        const static std::vector<signed char> HEX_TO_DEC;
        const static std::unordered_map<std::string, int> PORTS;

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

        /**
         * Ensure that the path, params, query, and userinfo are properly escaped.
         *
         * In 'strict' mode, only entities that are both safe and not reserved characters
         * are unescaped. In non-strict mode, entities that are safe are unescaped.
         */
        Url& escape(bool strict=false);

        /**
         * Remove any params or queries that appear in the blacklist.
         *
         * The blacklist should contain only lowercased strings, and the comparison is
         * done in a case-insensitive way.
         */
        Url& deparam(const std::unordered_set<std::string>& blacklist);

        /**
         * Put queries and params in sorted order.
         *
         * To ensure consistent comparisons, escape should be called beforehand.
         */
        Url& sort_query();

        /**
         * Remove the port if it's the default for the scheme.
         */
        Url& remove_default_port();

        /**
         * Remove the userinfo portion.
         */
        Url& deuserinfo();

        /**
         * Remove the fragment.
         */
        Url& defrag();

        /**
         * Punycode the hostname.
         */
        Url& punycode();

        /**
         * Unpunycode the hostname.
         */
        Url& unpunycode();

    private:
        // Private, unimplemented to prevent use.
        Url();

        /**
         * Remove repeated, leading, and trailing instances of chr from the string.
         */
        void remove_repeats(std::string& str, const char chr);

        /**
         * Ensure all the provided characters are escaped if necessary
         */
        void escape(std::string& str, const CharacterClass& safe, bool strict);

        /**
         * Remove any params that match entries in the blacklist.
         */
        void remove_params(std::string& str, const std::unordered_set<std::string>& blacklist, const char separator);

        /**
         * Split the provided string by char, sort, join by char.
         */
        void split_sort_join(std::string& str, const char glue);

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
