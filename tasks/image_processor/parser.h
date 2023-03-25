#pragma once

#include "imagework.h"

#include <string_view>
#include <vector>

struct FilterDescription {
    std::string_view name;
    std::vector<std::string> params;
};

class Parser {
public:
    bool Parse(int argc, char* argv[]);
    std::string_view GetInputFileName() const;
    std::string_view GetOutputFileName() const;

    std::vector<FilterDescription> filters_to_apply;

private:
    std::string_view input_file_name_;
    std::string_view output_file_name_;

    static const int MIN_PARAM_NUM = 3;
    static const int INPUT_FILE_NAME_POS = 1;
    static const int OUTPUT_FILE_NAME_POS = 2;
};
