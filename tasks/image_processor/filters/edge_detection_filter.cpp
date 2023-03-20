#include "edge_detection_filter.h"
#include "grayscale_filter.h"

EdgeDetectionFilter::EdgeDetectionFilter(double threshold)
    : threshold_(static_cast<uint8_t>(threshold * Image::RgbMaxD)) {
}

void EdgeDetectionFilter::Apply(Image& image) {
    GrayscaleFilter grayscale_filter;
    ApplyMatrix(filter_matrix_, image);
    grayscale_filter.Apply(image);
    for (int32_t x = 0; x < image.bmp_info_header.height; ++x) {
        for (int32_t y = 0; y < image.bmp_info_header.width; ++y) {
            Pixel new_pixel = image.GetPixel(x, y);
            if (new_pixel.r < threshold_) {
                new_pixel.r = 0;
                new_pixel.g = 0;
                new_pixel.b = 0;
            } else {
                new_pixel.r = Image::RgbMaxI;
                new_pixel.g = Image::RgbMaxI;
                new_pixel.b = Image::RgbMaxI;
            }
            image.ChangePixel(x, y, new_pixel);
        }
    }
}
