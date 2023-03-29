#pragma once

#include "base_filter.h"
#include "image_matrix.h"

class GaussianBlurFilter : public BaseFilter {
public:
    explicit GaussianBlurFilter(double sigma);

    void Apply(Image& image) override;

private:
    double sigma_ = 0;
};
