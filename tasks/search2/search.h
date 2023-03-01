#pragma once

#include <algorithm>
#include <ctype.h>
#include <string_view>
#include <vector>
#include <unordered_map>

class SearchEngine {
public:
    void BuildIndex(std::string_view text);
    std::vector<std::string_view> Search(std::string_view query, size_t results_count) const;

private:
    auto ParseQuery(std::string_view query) const;
    auto CalcRelevance(const auto& unique_words) const;
    auto FetchTop(const auto& relevance, size_t results_count) const;
    std::vector<std::string_view> text_by_lines_;
    std::vector<std::vector<std::string_view>> text_by_words_;
};
