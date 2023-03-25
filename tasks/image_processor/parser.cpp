#include "parser.h"

#include <string>
#include <string.h>
#include <cmath>

bool Parser::Parse(int argc, char** argv) {
    if (argc <= MIN_PARAM_NUM) {
        return false;
    }
    input_file_name_ = argv[INPUT_FILE_NAME_POS];
    output_file_name_ = argv[OUTPUT_FILE_NAME_POS];
    if (argv[OUTPUT_FILE_NAME_POS + 1][0] != '-') {
        return false;
    }
    FilterDescription filter_description;
    for (int i = OUTPUT_FILE_NAME_POS + 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if (!filter_description.name.empty()) {
                filters_to_apply.push_back(filter_description);
            }
            std::string_view filter = std::string_view(argv[i]).substr(1, strlen(argv[i]));
            filter_description.name = filter;
            filter_description.params = {};
        } else {
            filter_description.params.push_back(argv[i]);
        }
    }
    if (!filter_description.name.empty()) {
        if (filter_description.name == "blur" && !filters_to_apply.empty() && filters_to_apply.back().name == "blur") {
            double sigma = std::stod(filters_to_apply.back().params.at(0));
            double new_sigma = std::stod(filter_description.params.at(0));
            filters_to_apply.pop_back();
            FilterDescription new_blur;
            new_blur.name = "blur";
            std::string new_param = std::to_string(sqrt(sigma * sigma + new_sigma * new_sigma));
            new_blur.params.push_back(new_param);
            filter_description = new_blur;
        }
        filters_to_apply.push_back(filter_description);
    }
    return true;
}

std::string_view Parser::GetInputFileName() const {
    return input_file_name_;
}

std::string_view Parser::GetOutputFileName() const {
    return output_file_name_;
}