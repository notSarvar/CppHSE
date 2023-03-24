add_executable(
    image_processor
    image_processor.cpp
        filtersmanager.h
        parser.h
        filters/base_filter.h
        filters/crop_filter.cpp
        imagework.cpp
        filters/sharpening_filter.h
        filters/sharpening_filter.cpp
        filters/edge_detection_filter.cpp
        filters/gaussian_blur_filter.cpp
        filters/grayscale_filter.cpp
        filters/negative_filter.cpp
        parser.cpp
        helper.h
        helper.cpp
        filtersmanager.cpp filters/emboss_filter.h filters/emboss_filter.cpp filters/crystallize.h filters/crystallize.cpp)
