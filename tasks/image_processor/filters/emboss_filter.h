#ifndef CPP_HSE_TASKS_IMAGE_PROCESSOR_FILTERS_EMBOSS_FILTER_H_
#define CPP_HSE_TASKS_IMAGE_PROCESSOR_FILTERS_EMBOSS_FILTER_H_
#include "base_filter.h"
#include "image_matrix.h"

class EmbossFilter : public BaseFilter {
public:
    void Apply(Image& image) override;

private:
    const MatrixD filter_matrix_ = {{-1, -1, 0}, {-1, 0, 1}, {0, 1, 1}};
};

#endif  // CPP_HSE_TASKS_IMAGE_PROCESSOR_FILTERS_EMBOSS_FILTER_H_
