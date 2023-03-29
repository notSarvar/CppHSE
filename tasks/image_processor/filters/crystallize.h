#pragma once

#include "base_filter.h"

class CrystallizeFilter : public BaseFilter {
public:
    explicit CrystallizeFilter(int block_size);
    void Apply(Image &image) override;

private:
    int32_t block_size_ = 0;
};
