#include "filtersmanager.h"
#include "helper.h"

#include "filters/crop_filter.h"
#include "filters/grayscale_filter.h"
#include "filters/negative_filter.h"
#include "filters/edge_detection_filter.h"
#include "filters/sharpening_filter.h"
#include "filters/gaussian_blur_filter.h"
#include "filters/emboss_filter.h"
#include "filters/crystallize.h"

#include <string_view>
#include <stdexcept>

BaseFilter* MakeNegativeFilter(const FilterDescription& d) {
    if (d.name != "neg") {
        throw std::invalid_argument("wrong filter name");
    }
    return new NegativeFilter;
}

BaseFilter* MakeCropFilter(const FilterDescription& d) {
    if (d.name != "crop") {
        throw std::invalid_argument("wrong filter name");
    }
    try {
        if (d.params.size() != 2) {
            throw std::exception();
        }
        int32_t new_width = std::stoi(d.params.at(0));
        int32_t new_height = std::stoi(d.params.at(1));
        if (new_height <= 0 || new_width <= 0) {
            throw std::exception();
        }
        return new CropFilter(new_width, new_height);
    } catch (std::exception&) {
        throw std::invalid_argument("wrong crop params");
    }
}

BaseFilter* MakeGrayscaleFilter(const FilterDescription& d) {
    if (d.name != "gs") {
        throw std::invalid_argument("wrong filter name");
    }
    return new GrayscaleFilter;
}

BaseFilter* MakeSharpeningFilter(const FilterDescription& d) {
    if (d.name != "sharp") {
        throw std::invalid_argument("wrong filter name");
    }
    return new SharpeningFilter();
}

BaseFilter* MakeEdgeDetectionFilter(const FilterDescription& d) {
    if (d.name != "edge") {
        throw std::invalid_argument("wrong filter name");
    }
    try {
        std::string str_threshold = d.params.at(0);
        double threshold = std::stod(str_threshold.c_str());
        if (threshold < 0 || 1 < threshold) {
            throw std::exception();
        }
        return new EdgeDetectionFilter(threshold);
    } catch (std::exception&) {
        throw std::invalid_argument("wrong edge params");
    }
}

BaseFilter* MakeGaussianBlurFilter(const FilterDescription& d) {
    if (d.name != "blur") {
        throw std::invalid_argument("wrong filter name");
    }
    try {
        double sigma = std::stod(d.params.at(0));
        return new GaussianBlurFilter(sigma);
    } catch (std::exception&) {
        throw std::invalid_argument("wrong blur params");
    }
}

BaseFilter* MakeEmbossFilter(const FilterDescription& d) {
    if (d.name != "emboss") {
        throw std::invalid_argument("wrong filter name");
    }
    return new EmbossFilter();
}

BaseFilter* MakeCrystallizeFilter(const FilterDescription& d) {
    if (d.name != "crystal") {
        throw std::invalid_argument("wrong filter name");
    }
    try {
        std::string str_block_size = d.params.at(0);
        int block_size = std::stoi(str_block_size.c_str());
        if (block_size < 1) {
            throw std::exception();
        }
        return new CrystallizeFilter(block_size);
    } catch (std::exception&) {
        throw std::invalid_argument("wrong crystal params");
    }
}

FilterGenerator FilterApplicator::ApplyFilter(std::string_view name) {
    if (filters_list_.find(name) != filters_list_.end()) {
        return filters_list_[name];
    }
    return nullptr;
}
