#pragma once

#include <algorithm>
#include <ctype.h>
#include <cmath>
#include <set>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

class SearchEngine {
public:
    void BuildIndex(std::string_view text);
    std::vector<std::string_view> Search(std::string_view query, size_t results_count) const;
private:
    std::vector<std::string_view> text_by_lines;
    std::vector<std::vector<std::string_view>> text_by_words_;
};
