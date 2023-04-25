#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    bool is_pal = true;
    std::string some_string;
    for (uint64_t i = 0; i < str.length(); i++) {
        if (str[i] != ' ') {
            some_string += str[i];
        }
    }
    for (uint64_t i = 0; i < (some_string.length() + 1) / 2; i++) {
        if (some_string[i] != some_string[some_string.length() - 1 - i]) {
            is_pal = false;
        }
    }
    return is_pal;
}
