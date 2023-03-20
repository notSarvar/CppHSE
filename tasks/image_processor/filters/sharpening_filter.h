#pragma once

#include "base_filter.h"
#include "image_matrix.h"

class SharpeningFilter : public BaseFilter {
public:
    void Apply(Image &image) override;

private:
    const MatrixI filter_matrix_ = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
};
