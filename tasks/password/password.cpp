#include "password.h"

bool ValidatePassword(const std::string& password) {
    bool ans_flag = true;

    if (password.size() < 8 or password.size() > 14) {
        ans_flag = false;
    }

    int cnt_special[5] = {0};

    for (char t : password) {
        int ascii_code = static_cast<int>(t);

        if (ascii_code < 33 or ascii_code > 126) {
            ans_flag = false;
            break;
        }

        switch (ascii_code) {
            case 97 ... 122:
                cnt_special[0] = 1;
                break;
            case 65 ... 90:
                cnt_special[1] = 1;
                break;
            case 48 ... 57:
                cnt_special[2] = 1;
                break;
            default:
                cnt_special[3] = 1;
        }
    }

    if (std::count(cnt_special, cnt_special + 4, 1) < 3) {
        ans_flag = false;
    }

    return ans_flag;
}
