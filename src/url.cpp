#include <algorithm>
#include <string>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

#include "url.h"

namespace Url
{

    /* Character classes */
    const std::string Url::GEN_DELIMS = ":/?#[]@";
    const std::string Url::SUB_DELIMS = "!$&'()*+,;=";
    const std::string Url::ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const std::string Url::DIGIT = "0123456789";
    const std::string Url::UNRESERVED = Url::ALPHA + Url::DIGIT + "-._~";
    const std::string Url::RESERVED = Url::GEN_DELIMS + Url::SUB_DELIMS;
    const std::string Url::PCHAR = Url::UNRESERVED + Url::SUB_DELIMS + ":@";
    const std::string Url::PATH = Url::PCHAR + "/";
    const std::string Url::QUERY = Url::PCHAR + "/?";
    const std::string Url::FRAGMENT = Url::PCHAR + "/?";
    const std::string Url::USERINFO = Url::UNRESERVED + Url::SUB_DELIMS + ":";
    const std::string Url::HEX = "0123456789ABCDEF";
    const std::string Url::SCHEME =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-.";
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
            if (url.substr(0, index).find_first_not_of(SCHEME) == std::string::npos)
            {
                // If there is nothing after the : or there are any non-digits, this is
                // the scheme
                if ((index + 1) >= url.length()
                    || url.find_first_not_of(DIGIT, index + 1) != std::string::npos)
                {
                    scheme_ = url.substr(0, index);
                    std::transform(
                        scheme_.begin(), scheme_.end(), scheme_.begin(), ::tolower);
                    position = index + 1;
                }
            }
        }

        // Search for the netloc
        if (url.substr(position, 2).compare("//") == 0)
        {
            // Skip the '//'
            position += 2;
            index = url.find_first_of("/?#", position);
            host_ = url.substr(position, index - position);
            position = index;

            // Extract any userinfo if there is any
            index = host_.find('@');
            if (index != std::string::npos)
            {
                userinfo_ = host_.substr(0, index);
                host_ = host_.substr(index + 1);
            }
            
            // Lowercase the hostname
            std::transform(host_.begin(), host_.end(), host_.begin(), ::tolower);

            // Try to find a port
            index = host_.find(':');
            if (index != std::string::npos)
            {
                std::string portText = host_.substr(index + 1);
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
            path_ = url.substr(position);

            index = path_.find('#');
            if (index != std::string::npos)
            {
                fragment_ = path_.substr(index + 1);
                path_.resize(index);
            }

            index = path_.find('?');
            if (index != std::string::npos)
            {
                size_t start = path_.find_first_not_of('?', index + 1);
                if (start != std::string::npos)
                {
                    query_ = path_.substr(start);
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
                params_ = path_.substr(index + 1);
                remove_repeats(params_, ';');
                path_.resize(index);
            }
        }
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
        std::vector<std::string> segments;
        bool directory = false;
        size_t previous = 0;
        for (size_t index = path_.find('/')
            ; index != std::string::npos
            ; previous = index + 1, index = path_.find('/', index + 1))
        {
            std::string segment = path_.substr(previous, index - previous);

            if (segment.empty())
            {
                // Skip empty segments
                continue;
            }

            if ((index - previous == 2) && segment.compare("..") == 0)
            {
                if (!segments.empty())
                {
                    segments.pop_back();
                }
                directory = true;
            }
            else if ((index - previous == 1) && path_[previous] == '.')
            {
                directory = true;
            }
            else
            {
                segments.push_back(segment);
                directory = false;
            }
        }

        // Handle the last segment
        std::string segment = path_.substr(previous);
        if (segment.empty() || segment.compare(".") == 0)
        {
            directory = true;
        }
        else if (segment.compare("..") == 0)
        {
            if (!segments.empty())
            {
                segments.pop_back();
            }
            directory = true;
        }
        else
        {
            segments.push_back(segment);
            directory = false;
        }

        // Assemble the new path
        if (segments.empty())
        {
            path_ = directory ? "/" : "";
        }
        else
        {
            std::string copy;
            for (auto it = segments.begin(); it != segments.end(); ++it)
            {
                copy.append("/");
                copy.append(*it);
            }
            if (directory)
            {
                copy.append("/");
            }
            path_ = copy;
        }

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
                path_ = other.path_.substr(0, other.path_.rfind('/') + 1);
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

    void Url::escape(std::string& str, const std::string& safe, bool strict)
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
                    if (!strict || (strict
                        && (safe.find(value) != std::string::npos)
                        && (RESERVED.find(value) == std::string::npos)))
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

            if (safe.find(copy[src]) == std::string::npos)
            {
                // Not safe -- replace with %XX
                str[dest++] = '%';
                str[dest++] = HEX[(copy[src] >> 4) & 0xF];
                str[dest++] = HEX[copy[src] & 0xF];
            }
            else
            {
                str[dest++] = copy[src];
            }
        }
        str.resize(dest);
    }

    Url& Url::deparam(const std::unordered_set<std::string>& blacklist)
    {
        remove_params(params_, blacklist, ';');
        remove_params(query_, blacklist, '&');
        return *this;
    }

    void Url::remove_params(std::string& str, const std::unordered_set<std::string>& blacklist, const char separator)
    {
        std::vector<std::string> pieces;
        size_t previous = 0;
        for (size_t index = str.find(separator)
            ; index != std::string::npos
            ; previous = index + 1, index = str.find(separator, previous))
        {
            std::string piece = str.substr(previous, index - previous);
            std::string name = piece.substr(0, piece.find('='));
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);

            if (blacklist.find(name) == blacklist.end())
            {
                pieces.push_back(piece);
            }
        }

        if (previous < str.length())
        {
            std::string piece = str.substr(previous);
            std::string name = piece.substr(0, piece.find('='));
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            if (blacklist.find(name) == blacklist.end())
            {
                pieces.push_back(piece);
            }
        }

        std::string copy;
        for (auto it = pieces.begin(); it != pieces.end();)
        {
            copy.append(*it);
            for (++it; it != pieces.end(); ++it)
            {
                copy.append(1, separator);
                copy.append(*it);
            }
        }
        str.assign(copy);
    }

    Url& Url::remove_default_port()
    {
        return *this;
    }

};
