#include "helper.h"

#include <iostream>

const std::string SYNTAX_INFO =
    "Program syntax: {program_name} {input_file} {output_file} [-{filter1} [params_for_filter1] ...] ...\n"
    "------------------------\n"
    "List of filters:\n"
    "Crop (-crop width height)\n"
    "Grayscale (-gs)\n"
    "Negative (-neg)\n"
    "Sharpening (-sharp)\n"
    "Edge Detection (-edge threshold) (0 < threshold < 1)\n"
    "Gaussian Blur (-blur sigma)\n"
    "Emboss Filter(-emboss)";  // An emboss filter gives a 3D shadow effect to the image, the result is very useful for
                               // a bumpmap

void Helper() {
    std::cout << SYNTAX_INFO;
}

void WrongFilter(std::string_view filter_name) {
    std::cout << "Error: " << filter_name << ". Incorrect filter." << std::endl;
}

void Exception(std::exception& exception) {
    std::cout << exception.what() << std::endl;
}
