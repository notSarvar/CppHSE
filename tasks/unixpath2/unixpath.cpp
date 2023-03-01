#include "unixpath.h"

UnixPath::UnixPath(std::string_view initial_dir) : initial_dir_(static_cast<std::string>(initial_dir) + '/') {
    absolute_path_ = initial_dir_;
}

void UnixPath::ChangeDirectory(std::string_view path) {
    relative_path_.clear();
    if (path.empty()) {
        return;
    }
    size_t prev_slash = 0;
    if (path[0] == '/') {
        absolute_path_ = "/";
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
            if (absolute_path_ == "/") {
                continue;
            }
            size_t last_slash = absolute_path_.rfind('/', absolute_path_.size() - 2);
            absolute_path_.erase(last_slash + 1);
        } else {
            prev_slash = i;
            if (absolute_path_.back() != '/') {
                absolute_path_ += '/';
            }
            absolute_path_ += cur_move;
            absolute_path_ += "/";
        }
    }
    if (absolute_path_.ends_with('/')) {
        absolute_path_.pop_back();
    }

    size_t i = 0;
    size_t last_common_dir = 0;
    absolute_path_.push_back('/');
    while (initial_dir_[i] == absolute_path_[i] && i < std::min(initial_dir_.size(), absolute_path_.size())) {
        if (initial_dir_[i] == '/') {
            last_common_dir = i;
        }
        ++i;
    }
    i = last_common_dir + 1;
    while (i < initial_dir_.size()) {
        if (initial_dir_[i] == '/') {
            relative_path_ += "../";
        }
        ++i;
    }
    if (relative_path_.empty()) {
        relative_path_ += "./";
    }

    relative_path_ += absolute_path_.substr(last_common_dir + 1);

    if (relative_path_.size() > 1 && relative_path_.back() == '/') {
        relative_path_.pop_back();
    }
    absolute_path_.pop_back();
}

std::string UnixPath::GetAbsolutePath() const {
    return absolute_path_;
}

std::string UnixPath::GetRelativePath() const {
    return relative_path_;
}