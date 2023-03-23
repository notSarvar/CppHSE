#include "gaussian_blur_filter.h"

#include <cmath>
#include <iostream>

GaussianBlurFilter::GaussianBlurFilter(double sigma) : sigma_(sigma) {
}

void GaussianBlurFilter::Apply(Image& image) {
    int dim = std::ceil(static_cast<int>(sigma_ * 3 * 2));

    double sum = 0;
    MatrixD gauss;
    gauss.resize(1);
    gauss[0].resize(2 * dim + 1);
    for (int x = -dim; x <= dim; ++x) {
        double exp_pow = -(x * x) / (2 * sigma_ * sigma_);
        double exp = pow(M_E, exp_pow);
        double exp_denum = sqrt(2 * M_PI * sigma_ * sigma_);
        gauss[0][x + dim] = exp / exp_denum;
        sum += exp / exp_denum;
    }

    for (int x = 0; x <= dim * 2; ++x) {
        gauss[0][x] /= sum;
    }

    ApplyMatrix(gauss, image);

    sum = 0;
    gauss.resize(2 * dim + 1);
    for (int i = 0; i < 2 * dim + 1; ++i) {
        gauss[i].resize(1);
    }
    for (int x = -dim; x <= dim; ++x) {
        double exp_pow = -(x * x) / (2 * sigma_ * sigma_);
        double exp = pow(M_E, exp_pow);
        double exp_denum = sqrt(2 * M_PI * sigma_ * sigma_);
        gauss[x + dim][0] = exp / exp_denum;
        sum += exp / exp_denum;
    }

    for (int x = 0; x <= dim * 2; ++x) {
        gauss[x][0] /= sum;
    }
    ApplyMatrix(gauss, image);
}
