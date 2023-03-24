#include <catch.hpp>
#include "imagework.h"
#include "filtersmanager.h"
#include "parser.h"
#include "../filters/crop_filter.h"
#include "../filters/negative_filter.h"
#include "../filters/grayscale_filter.h"
#include "../filters/sharpening_filter.h"
#include "../filters/edge_detection_filter.h"
#include "../filters/gaussian_blur_filter.h"
#include "../filters/emboss_filter.h"
#include "../filters/crystallize.h"

TEST_CASE("SwapEndian") {
    unsigned int a = 0xAABBCCDD;
    auto b = SwapEndian(a);

    REQUIRE(b == 0xDDCCBBAA);
    b = SwapEndian(b);

    REQUIRE(b == a);
}

TEST_CASE("ImageWorkCheck") {
    std::string p = "/Users/mahmudovseravgan/Downloads/image_processor-main 3/tests/test_pictures/example.bmp";
    auto i1 = Image(p);
    REQUIRE(i1.bmp_info_header.height == 12);
    i1.WriteBMP("/Users/mahmudovseravgan/Documents/pmi-2211-2-Sarvar-Yuldashev-notSarvar/tasks/image_processor/test_script/data/outt_flag.bmp");
    auto i2 = Image("/Users/mahmudovseravgan/Documents/pmi-2211-2-Sarvar-Yuldashev-notSarvar/tasks/image_processor/test_script/data/outt_flag.bmp");
    REQUIRE(i2.bmp_info_header.colors_important == i1.bmp_info_header.colors_important);
}
