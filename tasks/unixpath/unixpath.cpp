#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {

    if (path.empty()) {
        return static_cast<std::string>(current_working_dir);
    }

    std::string cur_dir = static_cast<std::string>(current_working_dir);
    size_t prev_slash = 0;
    if (path[0] == '/') {
        cur_dir = "/";
    }
    std::string_view cur_move;
    for (size_t i = 1; i < path.size(); ++i) {
        while (path[i] != '/' && i < path.size()) {
            ++i;
        }
        if (path[0] != '/' && prev_slash == 0) {
            cur_move = path.substr(0, i);
        } else {
            cur_move = path.substr(prev_slash + 1, i - prev_slash - 1);
        }
        if (cur_move.empty() || cur_move == ".") {
            prev_slash = i;
            continue;
        } else if (cur_move == "..") {
            prev_slash = i;
            if (cur_dir == "/") {
                continue;
            }
            size_t last_slash = cur_dir.rfind('/', cur_dir.size() - 2);
            cur_dir.erase(last_slash + 1);
        } else {
            prev_slash = i;
            if (cur_dir.back() != '/') {
                cur_dir += '/';
            }
            cur_dir += cur_move;
            cur_dir += "/";
        }
    }
    if (cur_dir.back() == '/' && cur_dir.size() > 1) {
        cur_dir.pop_back();
    }
    return cur_dir;
}
