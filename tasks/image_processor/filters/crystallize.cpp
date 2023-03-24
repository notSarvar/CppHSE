#include "crystallize.h"

CrystallizeFilter::CrystallizeFilter(int block_size) : block_size_(block_size){};

void CrystallizeFilter::Apply(Image &image) {
    for (int y = 0; y < image.bmp_info_header.height; y += block_size_) {
        for (int x = 0; x < image.bmp_info_header.width; x += block_size_) {
            uint8_t r = 0;
            uint8_t g = 0;
            uint8_t b = 0;
            int pixel_count = 0;
            for (int j = y; j < y + block_size_ && j < image.bmp_info_header.height; ++j) {
                for (int i = x; i < x + block_size_ && i < image.bmp_info_header.width; ++i) {
                    Pixel p = image.GetPixel(j, i);
                    r += p.r;
                    g += p.g;
                    b += p.b;
                    ++pixel_count;
                }
            }
            r /= pixel_count;
            g /= pixel_count;
            b /= pixel_count;

            for (int j = y; j < y + block_size_ && j < image.bmp_info_header.height; ++j) {
                for (int i = x; i < x + block_size_ && i < image.bmp_info_header.width; ++i) {
                    image.ChangePixel(j, i, {r, g, b});
                }
            }
        }
    }

}