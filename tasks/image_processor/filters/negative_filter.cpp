#include "negative_filter.h"

void NegativeFilter::Apply(Image& image) {
    for (int32_t x = 0; x < image.bmp_info_header.height; ++x) {
        for (int32_t y = 0; y < image.bmp_info_header.width; ++y) {
            Pixel new_pixel = image.GetPixel(x, y);
            new_pixel.r = Image::RgbMaxI - new_pixel.r;
            new_pixel.g = Image::RgbMaxI - new_pixel.g;
            new_pixel.b = Image::RgbMaxI - new_pixel.b;
            image.ChangePixel(x, y, new_pixel);
        }
    }
}
