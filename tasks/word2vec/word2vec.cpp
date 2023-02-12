#include "word2vec.h"

#include <vector>
#include <unordered_map>

const int64_t INF = 2e9;

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::unordered_map<std::string, int64_t> how_close;
    int64_t max_dist = -INF;
    for (size_t i = 1; i < vectors.size(); ++i) {
        int64_t sum = 0;
        for (size_t j = 0; j < vectors[i].size(); ++j) {
            sum += static_cast<int64_t>(vectors[0][j]) * static_cast<int64_t>(vectors[i][j]);
        }
        how_close[words[i]] = sum;
        max_dist = std::max(max_dist, sum);
    }
    std::vector<std::string> closest_words;
    for (const auto& i : words) {
        if (how_close[i] == max_dist) {
            closest_words.push_back(i);
        }
    }
    return closest_words;
}
