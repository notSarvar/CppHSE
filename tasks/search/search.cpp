#include "search.h"

#include <unordered_set>
#include <sstream>

bool operator==(const std::string_view& a, const std::string_view& b) {
    if (a.size() == b.size()) {
        for (size_t i = 0; i < a.size(); ++i) {
            if (tolower(a[i]) != tolower(b[i])) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::unordered_set<std::string_view> unique_words;
    int64_t prev_space = -1;
    for (size_t i = 0; i < query.size(); ++i) {
        while (isalpha(query[i]) && i < query.size()) {
            ++i;
        }
        unique_words.insert(query.substr(prev_space + 1, i - prev_space - 1));
        prev_space = static_cast<int64_t>(i);
    }



    return {};
}
