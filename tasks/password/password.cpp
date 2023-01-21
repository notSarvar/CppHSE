#include "password.h"

constexpr size_t MinLength = 8;
constexpr size_t ClassesCnt = 4;
constexpr size_t ClassesRequired = 3;
constexpr size_t MaxLength = 14;
constexpr size_t MinCodeRequired = 33;
constexpr size_t MaxCodeRequired = 126;

bool ValidatePassword(const std::string& password) {

    if (password.size() < MinLength || password.size() > MaxLength) {
        return false;
    }

    int cnt_special[ClassesCnt] = {0};

    for (char t : password) {

        if (t < MinCodeRequired || t > MaxCodeRequired) {
            return false;
        }

        if (islower(t)) {
            cnt_special[0] = 1;
        } else if (isupper(t)) {
            cnt_special[1] = 1;
        } else if (isdigit(t)) {
            cnt_special[2] = 1;
        } else {
            cnt_special[3] = 1;
        }
    }

    return std::count(cnt_special, cnt_special + 4, 1) >= ClassesRequired;
}
