#pragma once

#include "../imagework.h"

class BaseFilter {
public:
    virtual void Apply(Image &image) = 0;

    virtual ~BaseFilter(){};
};
