#include "crystallize.h"

CrystallizeFilter::CrystallizeFilter(int block_size) : block_size_(block_size){};

void CrystallizeFilter::Apply(Image &image) {
    for (int32_t x = 0; x < image.bmp_info_header.height; x += block_size_) {
        for (int32_t y = 0; y < image.bmp_info_header.width; y += block_size_) {
            int32_t r = 0;
            int32_t g = 0;
            int32_t b = 0;
            int32_t pixel_count = 0;

            for (int32_t i = x; i < x + block_size_ && i < image.bmp_info_header.height; ++i) {
                for (int32_t j = y; j < y + block_size_ && j < image.bmp_info_header.width; ++j) {
                    Pixel p = image.GetPixel(i, j);
                    r += p.r;
                    g += p.g;
                    b += p.b;
                    ++pixel_count;
                }
            }
            r /= pixel_count;
            g /= pixel_count;
            b /= pixel_count;
            for (int32_t i = x; i < x + block_size_ && i < image.bmp_info_header.height; ++i) {
                for (int32_t j = y; j < y + block_size_ && j < image.bmp_info_header.width; ++j) {
                    image.ChangePixel(i, j,
                                      {static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b)});
                }
            }
        }
    }
}