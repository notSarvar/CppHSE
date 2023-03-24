#ifndef CPP_HSE_TASKS_IMAGE_PROCESSOR_FILTERS_CRYSTALLIZE_H_
#define CPP_HSE_TASKS_IMAGE_PROCESSOR_FILTERS_CRYSTALLIZE_H_

#include "base_filter.h"

class CrystallizeFilter : public BaseFilter {
public:
    explicit CrystallizeFilter(int block_size);
    void Apply(Image &image) override;

private:
    int block_size_ = 0;
};

#endif  // CPP_HSE_TASKS_IMAGE_PROCESSOR_FILTERS_CRYSTALLIZE_H_
