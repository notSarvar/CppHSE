add_library(contrib_catch_main
  contrib/catch/catch_main.cpp ../tasks/image_processor/tests/test_image.cpp)

target_include_directories(contrib_catch_main
  PUBLIC contrib/catch)
