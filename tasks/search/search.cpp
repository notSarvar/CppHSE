#include "search.h"

#include <set>
#include <unordered_map>
#include <vector>
#include <ctype.h>
#include <cmath>
#include <algorithm>

 #include <iostream>

bool Comp(const std::pair<double, std::string_view>& a, const std::pair<double, std::string_view>& b) {
    return (a.first - b.first > 0);
}

const auto& cmp = [](const std::string_view& a, const std::string_view& b) {
    for (size_t i = 0; i < std::min(a.size(), b.size()); ++i) {
        if (a[i] == b[i]) {
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
    size_t prev_space = 0;
    for (size_t i = 1; i < query.size(); ++i) {
        while (isalpha(query[i]) && i < query.size()) {
            ++i;
        }
        if (prev_space == 0 && isalpha(query[0]) && !query.substr(0, i).empty()) {
            unique_words.insert(query.substr(0, i));
        } else if (!query.substr(prev_space + 1, i - prev_space - 1).empty()) {
            unique_words.insert(query.substr(prev_space + 1, i - prev_space - 1));
        }

        prev_space = i;
    }

    size_t new_line = 0;
    std::string_view line;
    std::unordered_map<std::string_view, std::pair<std::string_view, size_t>> occur_count;
    std::unordered_map<std::string_view, size_t> line_words_cnt;
    std::vector<std::string_view> cur_text;
    do {
        new_line = text.find('\n');
        line = text.substr(0, new_line);
        text.remove_prefix(new_line + 1);
        line_words_cnt[line] = 0;
        size_t prev_space1 = 0;
        std::string_view word;
        cur_text.push_back(line);
        for (size_t i = 1; i < line.size(); ++i) {
            while (isalpha(line[i]) && i < line.size()) {
                ++i;
            }
            if (prev_space1 == 0 && isalpha(line[0])) {
                word = line.substr(0, i);
            } else {
                word = line.substr(prev_space1 + 1, i - prev_space1 - 1);
            }
            prev_space1 = i;

            for (const auto& w : unique_words) {
                if (w == word) {
                    occur_count[line].first = w;
                    ++occur_count[line].second;
                }
            }
            ++line_words_cnt[line];
        }
    } while (new_line < text.size());

    std::unordered_map<std::string_view, double> idfs;
    std::unordered_map<std::string_view, std::vector<std::pair<std::string_view, double>>> tfs;
    for (const auto& i : unique_words) {
        size_t occur_in_docs_cnt = 0;
        for (const auto& j : occur_count) {
            if (j.second.first == i) {
                tfs[j.first].push_back(
                    {i, static_cast<double>(j.second.second) / static_cast<double>(line_words_cnt[j.first])});
                ++occur_in_docs_cnt;
            }
        }
        idfs[i] = std::log(static_cast<double>(line_words_cnt.size()) / static_cast<double>(occur_in_docs_cnt));
    }
    double relevance = 0;
    std::vector<std::pair<double, std::string_view>> sorted_lines;
    for (const auto& i : cur_text) {
        relevance = 0;
        for (const auto& j : tfs[i]) {
            relevance += (j.second * idfs[j.first]);
        }
        if (relevance > 0) {
            sorted_lines.push_back({relevance, i});
        }
    }

    std::sort(sorted_lines.begin(), sorted_lines.end(), Comp);
//        for (const auto& i : sorted_lines) {
//            std::cout << i.second << "\n";
//        }

    std::vector<std::string_view> search_result;
    for (const auto& i : sorted_lines) {
        if (results_count-- == 0) {
            break;
        }
        search_result.push_back(i.second);
    }
    return search_result;
}
