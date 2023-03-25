#include "filtersmanager.h"

#include "filters/crop_filter.h"
#include "filters/grayscale_filter.h"
#include "filters/negative_filter.h"
#include "filters/edge_detection_filter.h"
#include "filters/sharpening_filter.h"
#include "filters/gaussian_blur_filter.h"
#include "filters/emboss_filter.h"
#include "filters/crystallize.h"

#include <string>
#include <string_view>
#include <stdexcept>

BaseFilter* MakeNegativeFilter(const FilterDescription& d) {
    if (d.name != "neg") {
        throw std::invalid_argument("wrong filter flag - " + std::string(d.name) + "expected - neg");
    }
    return new NegativeFilter;
}

BaseFilter* MakeCropFilter(const FilterDescription& d) {
    if (d.name != "crop") {
        throw std::invalid_argument("wrong filter flag - " + std::string(d.name) + "expected - crop");
    }

    if (d.params.size() != 2) {
        throw std::invalid_argument("Wrong crop params. Crop filter needs 2 params. Check it and try again");
    }
    int32_t new_width = std::stoi(d.params.at(0));
    int32_t new_height = std::stoi(d.params.at(1));
    if (new_height <= 0 || new_width <= 0) {
        throw std::invalid_argument(
            "Wrong crop params. Crop params must be greter or equal integer numbers. Check it and try again");
    }
    return new CropFilter(new_width, new_height);
}

BaseFilter* MakeGrayscaleFilter(const FilterDescription& d) {
    if (d.name != "gs") {
        throw std::invalid_argument("wrong filter flag - " + std::string(d.name) + "expected - gs");
    }
    return new GrayscaleFilter;
}

BaseFilter* MakeSharpeningFilter(const FilterDescription& d) {
    if (d.name != "sharp") {
        throw std::invalid_argument("wrong filter flag - " + std::string(d.name) + "expected - sharp");
    }
    return new SharpeningFilter();
}

BaseFilter* MakeEdgeDetectionFilter(const FilterDescription& d) {
    if (d.name != "edge") {
        throw std::invalid_argument("wrong filter flag - " + std::string(d.name) + "expected - edge");
    }
    double threshold = std::stod(d.params.at(0).c_str());
    if (threshold < 0 || 1 < threshold) {
        throw std::invalid_argument(
            "Wrong edge params. Threshold must be less than 1 and more than 0. Check it and try again.");
    }
    return new EdgeDetectionFilter(threshold);
}

BaseFilter* MakeGaussianBlurFilter(const FilterDescription& d) {
    if (d.name != "blur") {
        throw std::invalid_argument("wrong filter flag - " + std::string(d.name) + "expected - blur");
    }
    try {
        double sigma = std::stod(d.params.at(0));
        return new GaussianBlurFilter(sigma);
    } catch (std::exception&) {
        throw std::invalid_argument("Wrong blur param.");
    }
}

BaseFilter* MakeEmbossFilter(const FilterDescription& d) {
    if (d.name != "emboss") {
        throw std::invalid_argument("wrong filter flag - " + std::string(d.name) + "expected - emboss");
    }
    return new EmbossFilter();
}

BaseFilter* MakeCrystallizeFilter(const FilterDescription& d) {
    if (d.name != "crystal") {
        throw std::invalid_argument("wrong filter flag - " + std::string(d.name) + "expected - crystal");
    }
    int block_size = std::stoi(d.params.at(0).c_str());
    if (block_size < 1) {
        throw std::invalid_argument("Wrong crystal params. Block size must be greater or equal 1.");
    }
    return new CrystallizeFilter(block_size);
}

const FilterGenerator FilterApplicator::GetFilter(std::string_view name) {
    if (auto i = filters_list_.find(name); i != filters_list_.end()) {
        return i->second;
    }
    return nullptr;
}
