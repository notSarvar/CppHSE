#pragma once

#include <string>
#include <string_view>

class UnixPath {
public:
    explicit UnixPath(std::string_view initial_dir);

    void ChangeDirectory(std::string_view path);

    std::string GetAbsolutePath() const;
    std::string GetRelativePath() const;

private:
    const std::string initial_dir_;
    std::string cur_dir_;
    std::string absolute_path_;
    std::string relative_path_;
};
