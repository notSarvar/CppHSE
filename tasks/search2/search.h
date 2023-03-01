#pragma once

#include <string_view>
#include <vector>

class SearchEngine {
public:
    void BuildIndex(std::string_view text);
    std::vector<std::string_view> Search(std::string_view query, size_t results_count) const;

private:
    std::vector<std::pair<double, size_t>> CalcRelevance(const auto& unique_words) const;
    std::vector<std::string_view> FetchTop(const auto& relevance, size_t results_count) const;

    std::vector<std::string_view> text_by_lines_;
    std::vector<std::vector<std::string_view>> text_by_words_;
};
