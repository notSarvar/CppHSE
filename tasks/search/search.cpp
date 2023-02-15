#include "search.h"

#include <set>
#include <unordered_map>
#include <vector>
#include <ctype.h>
#include <cmath>
#include <algorithm>
#include <string>

const long double EPS = 1e-7;

bool ByRelevance(const std::pair<long double, std::size_t>& a, const std::pair<long double, std::size_t>& b) {
    if ((a.first - b.first) < EPS) {
        return false;
    }
    return true;
}

const auto& cmp = [](const std::string_view& a, const std::string_view& b) {
    for (size_t i = 0; i < std::min(a.size(), b.size()); ++i) {
        if (tolower(a[i]) == tolower(b[i])) {
            continue;
        }
        return tolower(a[i]) < tolower(b[i]);
    }
    return a.size() < b.size();
};

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
    std::set<std::string_view, decltype(cmp)> unique_words(cmp);
    size_t isnt_alpha = 0;
    for (size_t i = 1; i < query.size(); ++i) {
        while (isalpha(query[i]) && i < query.size()) {
            ++i;
        }
        if (isnt_alpha == 0 && isalpha(query[0]) && !query.substr(0, i).empty()) {
            unique_words.insert(std::string_view{query.data(), i});
        } else if (!std::string_view{query.data() + isnt_alpha + 1, i - isnt_alpha - 1}.empty()) {
            unique_words.insert(std::string_view{query.data() + isnt_alpha + 1, i - isnt_alpha - 1});
        }
        isnt_alpha = i;
    }

    size_t new_line = 0;
    std::string_view line;
    std::vector<std::vector<std::string_view>> cur_text;
    std::vector<std::string_view> text_by_lines;
    do {
        new_line = text.find('\n');
        if (new_line == std::string::npos) {
            new_line = text.size();
        }
        line = text.substr(0, new_line);
        text_by_lines.push_back(line);
        isnt_alpha = 0;
        std::string_view word;
        std::vector<std::string_view> cur_line;
        for (size_t i = 1; i < line.size(); ++i) {
            while (isalpha(line[i]) && i < line.size()) {
                ++i;
            }
            if (isnt_alpha == 0 && isalpha(line[0])) {
                word = std::string_view{line.data(), i};
            } else if (!std::string_view{line.data() + isnt_alpha + 1, i - isnt_alpha - 1}.empty()) {
                word = std::string_view{line.data() + isnt_alpha + 1, i - isnt_alpha - 1};
            }
            isnt_alpha = i;
            cur_line.push_back(word);
        }
        cur_text.push_back(cur_line);
        if (new_line == text.size()) {
            break;
        }
        text.remove_prefix(new_line + 1);
    } while (!text.empty());

    std::vector<std::unordered_map<std::string_view, size_t>> occur_cnt(cur_text.size());
    for (size_t i = 0; i < cur_text.size(); ++i) {
        for (const auto& j : unique_words) {
            for (size_t k = 0; k < cur_text[i].size(); ++k) {
                if (cur_text[i][k] == j) {
                    ++occur_cnt[i][j];
                }
            }
        }
    }

    std::unordered_map<std::string_view, long double> idfs;
    for (const auto& i : unique_words) {
        size_t occurs = 0;
        for (size_t j = 0; j < occur_cnt.size(); ++j) {
            if (occur_cnt[j].count(i)) {
                ++occurs;
            }
        }
        idfs[i] = logl(static_cast<long double>(cur_text.size()) / static_cast<long double>(occurs));
    }

    std::vector<std::pair<long double, size_t>> relevance(cur_text.size());
    for (size_t i = 0; i < occur_cnt.size(); ++i) {
        relevance[i] = {0, i};
        for (const auto& j : occur_cnt[i]) {
            relevance[i].first +=
                (static_cast<long double>(j.second) / static_cast<long double>(cur_text[i].size())) * idfs[j.first];
        }
    }

    std::stable_sort(relevance.begin(), relevance.end(), ByRelevance);

    std::vector<std::string_view> search_result;
    for (const auto& i : relevance) {
        if (results_count-- == 0) {
            break;
        }
        if (i.first > EPS) {
            search_result.push_back(text_by_lines[i.second]);
        }
    }
    return search_result;
}