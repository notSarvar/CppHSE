#include "password.h"

#define min_length 8
#define max_length 14
#define cnt_of_specials 4
#define min_ascii 33
#define max_ascii 126
#define a_ascii 97
#define z_ascii 122
#define A_ascii 65
#define Z_ascii 90
#define zero_ascii 48
#define nine_ascii 57

bool ValidatePassword(const std::string& password) {
    bool ans_flag = true;

    if (password.size() < min_length or password.size() > max_length) {
        ans_flag = false;
    }

    int cnt_special[cnt_of_specials] = {0};

    for (char t : password) {
        int ascii_code = static_cast<int>(t);

        if (ascii_code < min_ascii or ascii_code > max_ascii) {
            ans_flag = false;
            break;
        }

        switch (ascii_code) {
            case a_ascii ... z_ascii:
                cnt_special[0] = 1;
                break;
            case A_ascii ... Z_ascii:
                cnt_special[1] = 1;
                break;
            case zero_ascii ... nine_ascii:
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
