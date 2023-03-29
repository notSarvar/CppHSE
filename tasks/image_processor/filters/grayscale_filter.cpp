#include "grayscale_filter.h"

void GrayscaleFilter::Apply(Image& image) {
    for (int32_t x = 0; x < image.bmp_info_header.height; ++x) {
        for (int32_t y = 0; y < image.bmp_info_header.width; ++y) {
            Pixel new_pixel = image.GetPixel(x, y);
            new_pixel.r = new_pixel.g = new_pixel.b =
                static_cast<uint8_t>(coef_r_ * new_pixel.r + coef_g_ * new_pixel.g + coef_b_ * new_pixel.b);
            image.ChangePixel(x, y, new_pixel);
        }
    }
}
