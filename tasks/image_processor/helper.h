#pragma once

#include <string_view>
#include <string>
#include <stdexcept>

const std::string SYNTAX_INFO =
    "Program syntax: {program_name} {input_file} {output_file} -{filter1} [params_for_filter1] [-{filter2} ...] ...\n"
    "------------------------\n"
    "List of filters:\n"
    "Crop (-crop width height)\n"
    "Grayscale (-gs)\n"
    "Negative (-neg)\n"
    "Sharpening (-sharp)\n"
    "Edge Detection (-edge threshold) (0 < threshold < 1)\n"
    "Gaussian Blur (-blur sigma)\n"
    "CrystallizeFilter (-crystal block size) (block size >= 1)\n"
    "Emboss Filter(-emboss)";  // An emboss filter gives a 3D shadow effect to the image, the result is very useful for
                               // a bumpmap

void WrongInputParams() {
    throw std::invalid_argument("Wrong params. Use following syntax\n" + SYNTAX_INFO);
}

void WrongFilter(std::string_view filter_name) {
    throw std::invalid_argument("Error:" + std::string(filter_name) + ". Incorrect filter.");
}
