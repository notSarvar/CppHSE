#include "gaussian_blur_filter.h"

#include <cmath>

GaussianBlurFilter::GaussianBlurFilter(double sigma) : sigma_(sigma) {
}

void GaussianBlurFilter::Apply(Image& image) {
    int dim = std::ceil(static_cast<int>(sigma_ * 3));

    double sum = 0;
    MatrixD gauss;
    MatrixD gauss1;

    gauss1.resize(2 * dim + 1);
    for (int i = 0; i < 2 * dim + 1; ++i) {
        gauss1[i].resize(1);
    }

    gauss.resize(1);
    gauss[0].resize(2 * dim + 1);
    for (int x = -dim; x <= dim; ++x) {
        double exp_pow = -(x * x) / (2 * sigma_ * sigma_);
        double exp = pow(M_E, exp_pow);
        double exp_denum = sqrt(2 * M_PI * sigma_ * sigma_);
        double val = exp / exp_denum;
        gauss[0][x + dim] = val;
        gauss1[x + dim][0] = val;
        sum += val;
    }

    for (int x = 0; x <= dim * 2; ++x) {
        gauss[0][x] /= sum;
        gauss1[x][0] /= sum;
    }

    ApplyMatrix(gauss, image);
    ApplyMatrix(gauss1, image);
}
