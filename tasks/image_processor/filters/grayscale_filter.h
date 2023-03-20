#pragma once

#include "base_filter.h"

class GrayscaleFilter : public BaseFilter {
public:
    void Apply(Image &image) override;

private:
    const double coef_r_ = 0.229;
    const double coef_g_ = 0.586;
    const double coef_b_ = 0.114;
};
