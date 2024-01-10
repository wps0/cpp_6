#ifndef REGEX_HELPER_H
#define REGEX_HELPER_H

#include <string>

namespace regex_helper {
    static bool is_letter(char c) {
        return ('a' <= c and c <= 'z') or
               ('A' <= c and c <= 'Z');
    }

    static std::string convert_regex(const std::string &pattern) {
        std::string ret;
        for (char c: pattern) {
            if (c == '*') { // match any character any number of times
                ret += '.';
            } else if (c == '?') { // match exactly one character
                c = '.';
            } else if (!is_letter(c))
                ret += '\\'; // add escape character

            ret += c;
        }

        return ret;
    }
}

#endif //REGEX_HELPER_H
