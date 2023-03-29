#pragma once
#include "filters/base_filter.h"
#include "parser.h"

#include <unordered_map>
#include <string_view>

using FilterGenerator = BaseFilter* (*)(const FilterDescription&);

BaseFilter* MakeNegativeFilter(const FilterDescription& d);
BaseFilter* MakeCropFilter(const FilterDescription& d);
BaseFilter* MakeGrayscaleFilter(const FilterDescription& d);
BaseFilter* MakeSharpeningFilter(const FilterDescription& d);
BaseFilter* MakeEdgeDetectionFilter(const FilterDescription& d);
BaseFilter* MakeGaussianBlurFilter(const FilterDescription& d);
BaseFilter* MakeEmbossFilter(const FilterDescription& d);
BaseFilter* MakeCrystallizeFilter(const FilterDescription& d);

class FilterApplicator {
public:
    const FilterGenerator GetFilter(std::string_view name);

private:
    std::unordered_map<std::string_view, FilterGenerator> filters_list_ = {
        {"neg", MakeNegativeFilter},     {"gs", MakeGrayscaleFilter},       {"crop", MakeCropFilter},
        {"sharp", MakeSharpeningFilter}, {"edge", MakeEdgeDetectionFilter}, {"blur", MakeGaussianBlurFilter},
        {"emboss", MakeEmbossFilter},    {"crystal", MakeCrystallizeFilter}};
};
