#include <algorithm>
#include <string>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <iterator>
#include <sstream>

#include "url.h"
#include "punycode.h"

namespace Url
{

    /* Character classes */
    const CharacterClass Url::GEN_DELIMS(":/?#[]@");
    const CharacterClass Url::SUB_DELIMS("!$&'()*+,;=");
    const CharacterClass Url::DIGIT("0123456789");
    const CharacterClass Url::ALPHA(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    const CharacterClass Url::UNRESERVED(
        Url::ALPHA.chars() + Url::DIGIT.chars() + "-._~");
    const CharacterClass Url::RESERVED(
        Url::GEN_DELIMS.chars() + Url::SUB_DELIMS.chars());
    const CharacterClass Url::PCHAR(
        Url::UNRESERVED.chars() + Url::SUB_DELIMS.chars() + ":@");
    const CharacterClass Url::PATH(
        Url::PCHAR.chars() + "/");
    const CharacterClass Url::QUERY(
        Url::PCHAR.chars() + "/?");
    const CharacterClass Url::FRAGMENT(
        Url::PCHAR.chars() + "/?");
    const CharacterClass Url::USERINFO(
        Url::UNRESERVED.chars() + Url::SUB_DELIMS.chars() + ":");
    const CharacterClass Url::HEX("0123456789ABCDEF");
    const CharacterClass Url::SCHEME(
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-.");
    const std::vector<signed char> Url::HEX_TO_DEC = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
         0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,

        -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

        -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
    };
    const std::unordered_map<std::string, int> Url::PORTS = {
        {"http", 80},
        {"https", 443}
    };

    Url::Url(const std::string& url): port_(0)
    {
        size_t position = 0;
        size_t index = url.find(':');
        if (index != std::string::npos)
        {
            // All the characters in our would-be scheme must be in SCHEME
            if (std::all_of(
                    url.begin(),
                    url.begin() + index,
                    [](char c) { return SCHEME(c); } ))
            {
                // If there is nothing after the : or there are any non-digits, this is
                // the scheme
                if ((index + 1) >= url.length()
                    || std::any_of(
                        url.begin() + index + 1,
                        url.end(),
                        [](char c) { return !DIGIT(c); }))
                {
                    scheme_.assign(url, 0, index);
                    std::transform(
                        scheme_.begin(), scheme_.end(), scheme_.begin(), ::tolower);
                    position = index + 1;
                }
            }
        }

        // Search for the netloc
        if ((url.length() - position) >= 1
            && url[position] == '/'
            && url[position + 1] == '/')
        {
            // Skip the '//'
            position += 2;
            index = url.find_first_of("/?#", position);
            host_.assign(url, position, index - position);
            position = index;

            // Extract any userinfo if there is any
            index = host_.find('@');
            if (index != std::string::npos)
            {
                userinfo_.assign(host_, 0, index);
                host_.assign(host_, index + 1, std::string::npos);
            }
            
            // Lowercase the hostname
            std::transform(host_.begin(), host_.end(), host_.begin(), ::tolower);

            // Try to find a port
            index = host_.find(':');
            if (index != std::string::npos)
            {
                std::string portText(host_, index + 1, std::string::npos);
                host_.resize(index);

                if (portText.empty())
                {
                    port_ = 0;
                }
                else
                {
                    try
                    {
                        port_ = std::stoi(portText, &index);

                        if (index != portText.length())
                        {
                            // Malformed port
                            throw UrlParseException("Port not a number: " + portText);
                        }

                        if (port_ > 65535)
                        {
                            throw UrlParseException("Port too high: " + portText);
                        }
                        else if (port_ < 0)
                        {
                            throw UrlParseException("Port negative: " + portText);
                        }
                    }
                    catch (const std::out_of_range&)
                    {
                        throw UrlParseException("Port out of integer range: " + portText);
                    }
                }
            }
        }

        if (position != std::string::npos)
        {
            path_.assign(url, position, std::string::npos);

            index = path_.find('#');
            if (index != std::string::npos)
            {
                fragment_.assign(path_, index + 1, std::string::npos);
                path_.resize(index);
            }

            index = path_.find('?');
            if (index != std::string::npos)
            {
                size_t start = path_.find_first_not_of('?', index + 1);
                if (start != std::string::npos)
                {
                    query_.assign(path_, start, std::string::npos);
                    remove_repeats(query_, '&');
                }
                else
                {
                    query_ = "";
                }
                path_.resize(index);
            }

            index = path_.find(';');
            if (index != std::string::npos)
            {
                params_.assign(path_, index + 1, std::string::npos);
                remove_repeats(params_, ';');
                path_.resize(index);
            }
        }
    }

    Url& Url::assign(const Url& other)
    {
        return (*this) = other;
    }

    bool Url::operator==(const Url& other) const
    {
        return (
            (scheme_   == other.scheme_  ) &&
            (userinfo_ == other.userinfo_) &&
            (host_     == other.host_    ) &&
            (port_     == other.port_    ) &&
            (path_     == other.path_    ) &&
            (params_   == other.params_  ) &&
            (query_    == other.query_   ) &&
            (fragment_ == other.fragment_)
        );
    }

    bool Url::operator!=(const Url& other) const
    {
        return !operator==(other);
    }

    bool Url::equiv(const Url& other)
    {
        Url self_(*this);
        Url other_(other);

        self_.sort_query()
             .defrag()
             .deuserinfo()
             .abspath()
             .escape()
             .punycode()
             .remove_default_port();
        other_.sort_query()
              .defrag()
              .deuserinfo()
              .abspath()
              .escape()
              .punycode()
              .remove_default_port();
        return self_ == other_;
    }

    void Url::remove_repeats(std::string& str, const char chr)
    {
        size_t dest = 0;
        // By initializing this to true, it also strips of leading instances of chr
        bool seen = true;
        for (size_t src = 0; src < str.length(); ++src)
        {
            if (!seen || (str[src] != chr))
            {
                str[dest++] = str[src];
            }
            seen = str[src] == chr;
        }
        // Remove the last character if it happens to be chr
        size_t length = ((dest > 0) && (str[dest - 1] == chr)) ? dest - 1 : dest;
        str.resize(length);
    }

    std::string Url::str() const
    {
        std::string result;

        if (!scheme_.empty())
        {
            result.append(scheme_);
            result.append("://");
        }
        else if (!host_.empty())
        {
            result.append("//");
        }

        if (!userinfo_.empty())
        {
            result.append(userinfo_);
            result.append("@");
        }

        if (!host_.empty())
        {
            result.append(host_);
        }
        
        if (port_)
        {
            result.append(":");
            result.append(std::to_string(port_));
        }

        if (path_.empty())
        {
            if (!result.empty())
            {
                result.append("/");
            }
        }
        else
        {
            result.append(path_);
        }

        if (!params_.empty())
        {
            result.append(";");
            result.append(params_);
        }

        if (!query_.empty())
        {
            result.append("?");
            result.append(query_);
        }

        if (!fragment_.empty())
        {
            result.append("#");
            result.append(fragment_);
        }

        return result;
    }

    Url& Url::abspath()
    {
        std::string copy;
        std::vector<size_t> segment_starts;
        bool directory = false;
        size_t previous = 0;
        size_t index = 0;
        for (index = path_.find('/')
            ; index != std::string::npos
            ; previous = index + 1, index = path_.find('/', index + 1))
        {
            // Skip empty segments
            if (index - previous == 0)
            {
                continue;
            }

            if ((index - previous == 2)
                && path_[previous] == '.'
                && path_[previous + 1] == '.')
            {
                if (!segment_starts.empty())
                {
                    copy.resize(segment_starts.back());
                    segment_starts.pop_back();
                }
                directory = true;
            }
            else if ((index - previous == 1) && path_[previous] == '.')
            {
                directory = true;
            }
            else
            {
                segment_starts.push_back(copy.length());
                copy.append(1, '/');
                copy.append(path_, previous, index - previous);
                directory = false;
            }
        }

        // Handle the last segment
        index = path_.length();
        if (previous == path_.length())
        {
            directory = true;
        }
        else if ((index - previous == 1) && path_[previous] == '.')
        {
            directory = true;
        }
        else if ((index - previous == 2)
                && path_[previous] == '.'
                && path_[previous + 1] == '.')
        {
            if (!segment_starts.empty())
            {
                copy.resize(segment_starts.back());
            }
            directory = true;
        }
        else
        {
            copy.append(1, '/');
            copy.append(path_, previous, index - previous);
            directory = false;
        }

        if (directory)
        {
            copy.append(1, '/');
        }
        path_.assign(copy);

        return *this;
    }

    Url& Url::relative_to(const Url& other)
    {
        // Support scheme-relative URLs
        if (scheme_.empty())
        {
            scheme_ = other.scheme_;
        }

        // If this is an absolute URL (or scheme-relative), return early
        if (!host_.empty()) {
            return *this;
        }

        // If it's not an absolute URL, we need to copy the other host and port
        host_ = other.host_;
        port_ = other.port_;
        userinfo_ = other.userinfo_;

        // If the path portion is absolute, then bail out early.
        if (!path_.empty() && path_.front() == '/')
        {
            return *this;
        }

        // Otherwise, this is a path that need to be evaluated relative to the other. If
        // there is no '/', then we just keep our current path if it's not empty.
        if (path_.empty())
        {
            if (params_.empty())
            {
                path_ = other.path_;
                params_ = other.params_;
                if (query_.empty())
                {
                    query_ = other.query_;
                }
            }
            else
            {
                path_.assign(other.path_, 0, other.path_.rfind('/') + 1);
            }

            if (fragment_.empty())
            {
                fragment_ = other.fragment_;
            }
        }
        else
        {
            size_t index = other.path_.rfind('/');
            if (index != std::string::npos)
            {
                path_ = other.path_.substr(0, index + 1) + path_;
            }
            else if (!host_.empty())
            {
                path_ = "/" + path_;
            }
        }

        return *this;
    }

    Url& Url::escape(bool strict)
    {
        escape(path_, PATH, strict);
        escape(query_, QUERY, strict);
        escape(params_, QUERY, strict);
        escape(userinfo_, USERINFO, strict);
        return *this;
    }

    void Url::escape(std::string& str, const CharacterClass& safe, bool strict)
    {
        std::string copy(str);
        size_t dest = 0;
        // Allocate space pessimistically -- if every entity is expanded, it will take 3x
        // the space.
        str.resize(str.length() * 3);
        for (size_t src = 0; src < copy.length(); ++src)
        {
            if (copy[src] == '%' && (copy.length() - src) >= 2)
            {
                // Read ahead to see if there's a valid escape sequence. If not, treat
                // this like a normal character.
                if (HEX_TO_DEC[copy[src+1]] != -1 && HEX_TO_DEC[copy[src+2]] != -1)
                {
                    int value = (
                        HEX_TO_DEC[copy[src+1]] * 16 + HEX_TO_DEC[copy[src+2]]);

                    // In strict mode, we can only unescape parameters if they are both
                    // safe and node reserved
                    if (!strict || (strict && safe(value) && !RESERVED(value)))
                    {
                        // Replace src + 2 with that byte, advance src to consume it and
                        // continue.
                        src += 2;
                        copy[src] = value;
                    }
                    else
                    {
                        str[dest++] = copy[src++];
                        str[dest++] = ::toupper(copy[src++]);
                        str[dest++] = ::toupper(copy[src]);
                        continue;
                    }
                }
            }

            if (!safe(copy[src]))
            {
                // Not safe -- replace with %XX
                str[dest++] = '%';
                str[dest++] = HEX.chars()[(copy[src] >> 4) & 0xF];
                str[dest++] = HEX.chars()[copy[src] & 0xF];
            }
            else
            {
                str[dest++] = copy[src];
            }
        }
        str.resize(dest);
    }

    Url& Url::unescape()
    {
        unescape(path_);
        unescape(query_);
        unescape(params_);
        unescape(userinfo_);
        return *this;
    }

    void Url::unescape(std::string& str)
    {
        std::string copy(str);
        size_t dest = 0;
        for (size_t src = 0; src < copy.length(); ++src, ++dest)
        {
            if (copy[src] == '%' && (copy.length() - src) >= 2)
            {
                // Read ahead to see if there's a valid escape sequence. If not, treat
                // this like a normal character.
                if (HEX_TO_DEC[copy[src+1]] != -1 && HEX_TO_DEC[copy[src+2]] != -1)
                {
                    int value = (
                        HEX_TO_DEC[copy[src+1]] * 16 + HEX_TO_DEC[copy[src+2]]);

                    // Replace src + 2 with that byte, advance src to consume it and
                    // continue.
                    src += 2;
                    str[dest] = value;
                    continue;
                }
            }
            
            // Either not a % or an incomplete entity
            str[dest] = copy[src];
        }
        str.resize(dest);
    }

    Url& Url::deparam(const std::unordered_set<std::string>& blacklist)
    {
        // Predicate is if it's present in the blacklist.
        auto predicate = [blacklist](std::string& name, const std::string& value)
        {
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            return blacklist.find(name) != blacklist.end();
        };

        remove_params(params_, predicate, ';');
        remove_params(query_, predicate, '&');
        return *this;
    }

    Url& Url::deparam(const deparam_predicate& predicate)
    {
        remove_params(params_, predicate, ';');
        remove_params(query_, predicate, '&');
        return *this;
    }

    void Url::remove_params(std::string& str,
                            const deparam_predicate& predicate,
                            char sep)
    {
        std::string copy;
        std::string piece;
        std::string name;
        std::string value;
        size_t previous = 0;
        for (size_t index = str.find(sep)
            ; index != std::string::npos
            ; previous = index + 1, index = str.find(sep, previous))
        {
            piece.assign(str, previous, index - previous);
            size_t position = piece.find('=');
            name.assign(piece, 0, position);
            value.clear();
            if (position != std::string::npos)
            {
                value.assign(piece, position + 1, std::string::npos);
            }

            if (!predicate(name, value))
            {
                copy.append(copy.empty() ? 0 : 1, sep);
                copy.append(piece);
            }
        }

        if (previous < str.length())
        {
            piece.assign(str, previous, std::string::npos);
            size_t position = piece.find('=');
            name.assign(piece, 0, position);
            value.clear();
            if (position != std::string::npos)
            {
                value.assign(piece, position + 1, std::string::npos);
            }

            if (!predicate(name, value))
            {
                copy.append(copy.empty() ? 0 : 1, sep);
                copy.append(piece);
            }
        }

        str.assign(copy);
    }

    Url& Url::sort_query()
    {
        split_sort_join(query_, '&');
        split_sort_join(params_, ';');
        return *this;
    }

    void Url::split_sort_join(std::string& str, const char glue)
    {
        // Return early if empty
        if (str.empty())
        {
            return;
        }

        // Split
        std::vector<std::string> pieces;
        std::stringstream stream(str);
        std::string item;
        while (getline(stream, item, glue))
        {
            pieces.push_back(item);
        }

        // Return early if it's just a single element
        if (pieces.size() == 1)
        {
            return;
        }

        // Sort
        std::sort(pieces.begin(), pieces.end());

        // Join (at this point we know that there's at least one element)
        std::stringstream output;
        for (auto it = pieces.begin(); it != (pieces.end() - 1); ++it)
        {
            output << *it << glue;
        }
        output << pieces.back();
        str.assign(output.str());
    }

    Url& Url::remove_default_port()
    {
        if (port_ && !scheme_.empty())
        {
            auto it = PORTS.find(scheme_);
            if (it != PORTS.end() && port_ == it->second)
            {
                port_ = 0;
            }
        }
        return *this;
    }

    Url& Url::deuserinfo()
    {
        userinfo_.clear();
        return *this;
    }

    Url& Url::defrag()
    {
        fragment_.clear();
        return *this;
    }

    Url& Url::punycode()
    {
        // Avoid any punycoding at all if none is needed
        if (!Punycode::needsPunycoding(host_))
        {
            return *this;
        }

        std::string encoded;

        auto last = host_.cbegin();
        for (auto it = host_.cbegin(); it != host_.cend(); ++it)
        {
            if (*it == '.')
            {
                if (Punycode::needsPunycoding(last, it))
                {
                    encoded.append("xn--");
                    Punycode::encode(encoded, last, it);
                }
                else
                {
                    encoded.append(last, it);
                }

                encoded.append(1, '.');
                last = it + 1;
            }
        }

        if (Punycode::needsPunycoding(last, host_.cend()))
        {
            encoded.append("xn--");
            Punycode::encode(encoded, last, host_.cend());
        }
        else
        {
            encoded.append(last, host_.cend());
        }

        host_.assign(encoded);

        return *this;
    }

    Url& Url::unpunycode()
    {
        std::string unencoded;
        std::string prefix;

        auto last = host_.cbegin();
        for (auto it = host_.cbegin(); it != host_.cend(); ++it)
        {
            if (*it == '.')
            {
                // Starts with 'xn--'
                size_t distance = it - last;
                if (distance > 4)
                {
                    prefix.assign(last, last + 4);
                    if (prefix == "xn--")
                    {
                        Punycode::decode(unencoded, last + 4, it);
                        unencoded.append(1, '.');
                        last = it + 1;
                        continue;
                    }
                }

                unencoded.append(last, it);
                unencoded.append(1, '.');
                last = it + 1;
            }
        }

        // Last segment
        size_t distance = host_.cend() - last;
        if (distance > 4)
        {
            prefix.assign(last, last + 4);
            if (prefix == "xn--")
            {
                Punycode::decode(unencoded, last + 4, host_.cend());
                host_.assign(unencoded);
                return *this;
            }
        }

        unencoded.append(last, host_.cend());
        host_.assign(unencoded);
        return *this;
    }

};
