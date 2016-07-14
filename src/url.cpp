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
    const std::string Url::SCHEME =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-.";

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
                query_ = path_.substr(index + 1);
                remove_repeats(query_, '?');
                remove_repeats(query_, '&');
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

};
