#include <catch.hpp>
#include "../filters/crop_filter.h"
#include "../filters/negative_filter.h"
#include "../filters/grayscale_filter.h"
#include "../filters/sharpening_filter.h"
#include "../filters/edge_detection_filter.h"
#include "../filters/gaussian_blur_filter.h"
#include "../filters/emboss_filter.h"

TEST_CASE("TestNegFilter") {
    Image i = Image("/Users/mahmudovseravgan/Documents/pmi-2211-2-Sarvar-Yuldashev-notSarvar/tasks/image_processor/test_script/data/flag.bmp");
    Image target = Image("/Users/mahmudovseravgan/Documents/pmi-2211-2-Sarvar-Yuldashev-notSarvar/tasks/image_processor/test_script/data/flag_neg.bmp");

    NegativeFilter filter = NegativeFilter();
    filter.Apply(i);
    REQUIRE(i.pixels == target.pixels);
}
