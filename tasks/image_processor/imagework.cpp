#include "imagework.h"

#include <bit>
#include <fstream>

Image::Image(const std::string_view &path) {
    std::ifstream input_file(std::string(path), std::ios_base::binary);

    if (!input_file.is_open()) {
        throw std::invalid_argument("Unreadable file");
    }

    input_file.read(reinterpret_cast<char *>(&bmp_file_header), sizeof(BMPHeaderFile));

    if constexpr (std::endian::native == std::endian::big) {
        bmp_file_header.offset_data = SwapEndian(bmp_file_header.offset_data);
        bmp_file_header.magic_bytes = SwapEndian(bmp_file_header.magic_bytes);
        bmp_file_header.file_size = SwapEndian(bmp_file_header.file_size);
    }

    if (bmp_file_header.magic_bytes != BMP_MAGIC_BYTES) {
        throw std::invalid_argument("Incorrect file format");
    }
    input_file.read(reinterpret_cast<char *>(&bmp_info_header), sizeof(BMPHeaderInfo));

    if constexpr (std::endian::native == std::endian::big) {
        bmp_info_header.size = SwapEndian(bmp_info_header.size);
        bmp_info_header.width = SwapEndian(bmp_info_header.width);
        bmp_info_header.height = SwapEndian(bmp_info_header.height);
        bmp_info_header.planes = SwapEndian(bmp_info_header.planes);
        bmp_info_header.bits_per_pixel = SwapEndian(bmp_info_header.bits_per_pixel);
        bmp_info_header.compression = SwapEndian(bmp_info_header.compression);
        bmp_info_header.image_size = SwapEndian(bmp_info_header.image_size);
        bmp_info_header.x_pixels_per_m = SwapEndian(bmp_info_header.x_pixels_per_m);
        bmp_info_header.y_pixels_per_m = SwapEndian(bmp_info_header.y_pixels_per_m);
        bmp_info_header.colors_used = SwapEndian(bmp_info_header.colors_used);
        bmp_info_header.colors_important = SwapEndian(bmp_info_header.colors_important);
    }

    if (bmp_info_header.size != BMP_INFO_HEADER_SIZE) {
        throw std::invalid_argument("Incorrect BMP bitmap header");
    }

    input_file.seekg(bmp_file_header.offset_data, input_file.beg);
    pixels.resize(bmp_info_header.width * bmp_info_header.height * 3);

    if (bmp_info_header.width % 4 == 0) {
        input_file.read(reinterpret_cast<char *>(pixels.data()), static_cast<std::streamsize>(pixels.size()));
    } else {
        size_t padding = bmp_info_header.width % 4;
        for (int32_t i = 0; i < bmp_info_header.height; ++i) {
            input_file.read(reinterpret_cast<char *>(pixels.data() + i * 3 * bmp_info_header.width),
                            bmp_info_header.width * 3);
            input_file.seekg(static_cast<int64_t>(padding), std::ios::cur);
        }
    }

    bmp_file_header.file_size = sizeof(bmp_file_header) + sizeof(bmp_info_header) + pixels.size();
    bmp_file_header.offset_data = sizeof(bmp_file_header) + sizeof(bmp_info_header);
}

void Image::WriteBMP(const std::string_view &path) {
    std::ofstream out_file(std::string(path), std::ios_base::binary);

    if (!out_file.is_open()) {
        throw std::invalid_argument("Unable to write file");
    }

    if constexpr (std::endian::native == std::endian::big) {
        bmp_file_header.offset_data = SwapEndian(bmp_file_header.offset_data);
        bmp_file_header.magic_bytes = SwapEndian(bmp_file_header.magic_bytes);
        bmp_file_header.file_size = SwapEndian(bmp_file_header.file_size);

        bmp_info_header.size = SwapEndian(bmp_info_header.size);
        bmp_info_header.width = SwapEndian(bmp_info_header.width);
        bmp_info_header.height = SwapEndian(bmp_info_header.height);
        bmp_info_header.planes = SwapEndian(bmp_info_header.planes);
        bmp_info_header.bits_per_pixel = SwapEndian(bmp_info_header.bits_per_pixel);
        bmp_info_header.compression = SwapEndian(bmp_info_header.compression);
        bmp_info_header.image_size = SwapEndian(bmp_info_header.image_size);
        bmp_info_header.x_pixels_per_m = SwapEndian(bmp_info_header.x_pixels_per_m);
        bmp_info_header.y_pixels_per_m = SwapEndian(bmp_info_header.y_pixels_per_m);
        bmp_info_header.colors_used = SwapEndian(bmp_info_header.colors_used);
        bmp_info_header.colors_important = SwapEndian(bmp_info_header.colors_important);
    }

    out_file.write(reinterpret_cast<char *>(&bmp_file_header), sizeof(BMPHeaderFile));
    out_file.write(reinterpret_cast<char *>(&bmp_info_header), sizeof(BMPHeaderInfo));

    if (bmp_info_header.width % 4 == 0) {
        out_file.write(reinterpret_cast<char *>(pixels.data()), static_cast<std::streamsize>(pixels.size()));
    } else {
        size_t padding = bmp_info_header.width % 4;
        char padding_rubbish[] = {0, 0, 0};
        for (int32_t i = 0; i < bmp_info_header.height; ++i) {
            out_file.write(reinterpret_cast<char *>(pixels.data() + i * 3 * bmp_info_header.width),
                           bmp_info_header.width * 3);
            out_file.write(padding_rubbish, static_cast<std::streamsize>(padding));
        }
    }

    out_file.flush();
    out_file.close();
}

Pixel Image::GetPixel(int32_t x, int32_t y) {
    uint8_t b = pixels[x * bmp_info_header.width * 3 + 3 * y + 0];
    uint8_t g = pixels[x * bmp_info_header.width * 3 + 3 * y + 1];
    uint8_t r = pixels[x * bmp_info_header.width * 3 + 3 * y + 2];
    return {r, g, b};
}

void Image::ChangePixel(int32_t x, int32_t y, Pixel new_pixel) {
    pixels[x * bmp_info_header.width * 3 + 3 * y + 0] = new_pixel.b;
    pixels[x * bmp_info_header.width * 3 + 3 * y + 1] = new_pixel.g;
    pixels[x * bmp_info_header.width * 3 + 3 * y + 2] = new_pixel.r;
}

void Image::Resize(int32_t width, int32_t height) {
    if (height > bmp_info_header.height || width > bmp_info_header.width || height <= 0 || width <= 0) {
        return;
    }
    std::vector<uint8_t> resized_pixels;
    for (int32_t i = bmp_info_header.height - height; i < bmp_info_header.height; ++i) {
        for (int32_t j = 0; j < width * 3; ++j) {
            resized_pixels.push_back(pixels[i * bmp_info_header.width * 3 + j]);
        }
    }
    pixels = resized_pixels;
    bmp_info_header.height = height;
    bmp_info_header.width = width;
    bmp_file_header.file_size = bmp_file_header.file_size - bmp_info_header.image_size + width * height * 3;
    bmp_info_header.image_size = width * height * 3;
}
