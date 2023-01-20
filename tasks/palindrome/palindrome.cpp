#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    std::string spaceless;
    for (char t : str) {
        if (t != ' ') {
            spaceless += t;
        }
    }
    size_t length = spaceless.size();
    for (size_t i = 0; i < length / 2; i++) {
        if (spaceless[i] != spaceless[length - i - 1]) {
            return false;
        }
    }
    return true;
}
