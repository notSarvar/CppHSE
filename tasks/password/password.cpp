#include "password.h"

constexpr size_t MIN_LENGTH = 8;
constexpr size_t CLASSES_CNT = 4;
constexpr size_t MAX_LENGTH = 14;
constexpr size_t MIN_CODE_REQUIRED = 33;
constexpr size_t MAX_CODE_REQUIRED = 126;

bool ValidatePassword(const std::string& password) {

    if (password.size() < MIN_LENGTH || password.size() > MAX_LENGTH) {
        return false;
    }

    int cnt_special[CLASSES_CNT] = {0};

    for (char t : password) {
        int ascii_code = static_cast<int>(t);

        if (ascii_code < MIN_CODE_REQUIRED || ascii_code > MAX_CODE_REQUIRED) {
            return false;
        }

        if (islower(ascii_code)) {
            cnt_special[0] = 1;
        }
        else if (isupper(ascii_code)) {
            cnt_special[1] = 1;
        }
        else if (isdigit(ascii_code)) {
            cnt_special[2] = 1;
        } else {
            cnt_special[3] = 1;
        }
    }

    return std::count(cnt_special, cnt_special + 4, 1) > 2;
}
