#ifndef REGEX_HELPER_H
#define REGEX_HELPER_H

#include <string>

namespace regex_helper {

    static std::string convert_regex(const std::string &pattern) {
        std::string ret;
        for (char c: pattern) {
            if (c == '*') { // match any character any number of times
                ret += '.';
            } else if (c == '?') { // match exactly one character
                c = '.';
            }

            ret += c;
        }

        return ret;
    }
}

#endif //REGEX_HELPER_H
