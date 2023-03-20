#pragma once

#include "base_filter.h"
#include "image_matrix.h"

class EdgeDetectionFilter : public BaseFilter {
public:
    explicit EdgeDetectionFilter(double threshold);
    void Apply(Image &image) override;

private:
    const MatrixI filter_matrix_ = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    const uint8_t threshold_ = 0;
};
