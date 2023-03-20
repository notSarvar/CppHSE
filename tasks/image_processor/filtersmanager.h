#ifndef CPP_HSE_TASKS_IMAGE_PROCESSOR_FILTERSMANAGER_H_
#define CPP_HSE_TASKS_IMAGE_PROCESSOR_FILTERSMANAGER_H_
#include "filters/base_filter.h"
#include "parser.h"

#include <map>
#include <string_view>

using FilterGenerator = BaseFilter* (*)(const FilterDescription&);

BaseFilter* MakeNegativeFilter(const FilterDescription& d);
BaseFilter* MakeCropFilter(const FilterDescription& d);
BaseFilter* MakeGrayscaleFilter(const FilterDescription& d);
BaseFilter* MakeSharpeningFilter(const FilterDescription& d);
BaseFilter* MakeEdgeDetectionFilter(const FilterDescription& d);
BaseFilter* MakeGaussianBlurFilter(const FilterDescription& d);
BaseFilter* MakeEmbossFilter(const FilterDescription& d);

class FilterApplicator{
public:
    FilterGenerator ApplyFilter(std::string_view name);

private:
    std::map<std::string_view, FilterGenerator> filters_list_ = {
        {"neg", MakeNegativeFilter},     {"gs", MakeGrayscaleFilter},       {"crop", MakeCropFilter},
        {"sharp", MakeSharpeningFilter}, {"edge", MakeEdgeDetectionFilter}, {"blur", MakeGaussianBlurFilter},
        {"emboss", MakeEmbossFilter}};
};

#endif
