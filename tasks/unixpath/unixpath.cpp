#include "unixpath.h"

// #include <iostream>

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {

    if (path.empty()) {
        return static_cast<std::string>(current_working_dir);
    }

    std::string cur_dir = static_cast<std::string>(current_working_dir);
    int64_t prev_slash = -1;
    if (path[0] == '/') {
        cur_dir = "/";
        prev_slash = 0;
    }

    std::string_view cur_move;
    for (size_t i = 1; i < path.size(); ++i) {
        while (path[i] != '/' && i < path.size()) {
            ++i;
        }
        cur_move = path.substr(prev_slash + 1, i - prev_slash - 1);
        if (cur_move.empty() || cur_move == ".") {
            prev_slash = static_cast<int64_t>(i);
            continue;
        } else if (cur_move == "..") {
            prev_slash = static_cast<int64_t>(i);
            if (cur_dir == "/") {
                continue;
            }
            size_t last_slash = cur_dir.rfind('/', cur_dir.size() - 2);
            //            std::cout<<last_slash <<"\n";
            cur_dir = cur_dir.substr(0, last_slash + 1);
        } else {
            prev_slash = static_cast<int64_t>(i);
            cur_dir += cur_move;
            cur_dir += "/";
        }
        //         std::cout << cur_dir << "\n";
    }
    if (cur_dir[cur_dir.size() - 1] == '/' && cur_dir.size() > 1) {
        cur_dir.erase(cur_dir.size() - 1);
    }
    // std::cout << "---------\n";
    return cur_dir;
}
