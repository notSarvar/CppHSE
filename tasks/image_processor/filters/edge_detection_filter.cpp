#include "edge_detection_filter.h"
#include "grayscale_filter.h"

#include <cmath>

EdgeDetectionFilter::EdgeDetectionFilter(double threshold)
    : threshold_(static_cast<uint8_t>(std::lround(threshold * Image::RgbMaxI))) {
}

void EdgeDetectionFilter::Apply(Image& image) {
    GrayscaleFilter grayscale_filter;
    grayscale_filter.Apply(image);
    ApplyMatrix(filter_matrix_, image);
    for (int32_t x = 0; x < image.bmp_info_header.height; ++x) {
        for (int32_t y = 0; y < image.bmp_info_header.width; ++y) {
            Pixel new_pixel = image.GetPixel(x, y);
            if (new_pixel.r <= threshold_) {
                new_pixel.r = new_pixel.g = new_pixel.b = 0;
            } else {
                new_pixel.r = new_pixel.g = new_pixel.b = Image::RgbMaxI;
            }
            image.ChangePixel(x, y, new_pixel);
        }
    }
}
