#include "emboss_filter.h"

void EmbossFilter::Apply(Image &image) {
    ApplyMatrix(filter_matrix_, image);
}