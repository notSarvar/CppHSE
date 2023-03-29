#pragma once

#include "base_filter.h"
#include "image_matrix.h"

class EmbossFilter : public BaseFilter {
public:
    void Apply(Image& image) override;

private:
    const MatrixD filter_matrix_ = {{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}};
};
