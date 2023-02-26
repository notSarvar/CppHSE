#include "unixpath.h"

UnixPath::UnixPath(std::string_view initial_dir) : cur_dir_(initial_dir){}

void UnixPath::ChangeDirectory(std::string_view path) {

    if (path.empty()) {
        return;
    }

    size_t prev_slash = 0;
    if (path[0] == '/') {
        this->cur_dir_ = "/";
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
            if (this->cur_dir_ == "/") {
                continue;
            }
            size_t last_slash = this->cur_dir_.rfind('/', cur_dir.size() - 2);
            this->cur_dir_.erase(last_slash + 1);
        } else {
            prev_slash = i;
            if (this->cur_dir_.back() != '/') {
                this->cur_dir_ += '/';
            }
            this->cur_dir_ += cur_move;
            this->cur_dir_ += "/";
        }
    }
    if (this->cur_dir_.back() == '/' && this->cur_dir_.size() > 1) {
        this->cur_dir_.pop_back();
    }
}

std::string UnixPath::GetAbsolutePath() const {

}

std::string UnixPath::GetRelativePath() const {

}