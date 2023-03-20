#include "sharpening_filter.h"

void SharpeningFilter::Apply(Image& image) {
    ApplyMatrix(filter_matrix_, image);
}