#include "parser.h"

#include <string>

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
        filters_to_apply.push_back(filter_description);
    }
    return true;
}

std::string Parser::GetInputFileName() const {
    return std::string{input_file_name_};
}

std::string Parser::GetOutputFileName() const {
    return std::string{output_file_name_};
}