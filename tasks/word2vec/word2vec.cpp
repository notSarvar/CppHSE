#include "word2vec.h"

#include <vector>
#include <unordered_map>

const int INF = 2e9;

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::unordered_map<std::string, int> how_close;
    int max_dist = -INF;
    for (int i = 1; i < vectors.size(); ++i) {
        int sum = 0;
        for (int j = 0; j < vectors[i].size(); ++j) {
            sum += vectors[0][j] * vectors[i][j];
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
// Ya znayu eto ne proidet
