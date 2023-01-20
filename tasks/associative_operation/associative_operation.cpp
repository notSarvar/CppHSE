#include "associative_operation.h"

bool IsAssociative(const std::vector<std::vector<size_t>>& table) {
    for (size_t i = 0; i < table.size(); ++i) {
        for (size_t j = 0; j < table[i].size(); ++j) {
            if (table[j][table[i][j]] != i or table[table[i][j]][i] != j) {
                return false;
            }
        }
    }
    return true;
}
