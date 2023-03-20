#ifndef CPP_HSE_TASKS_IMAGE_PROCESSOR_HELPER_H_
#define CPP_HSE_TASKS_IMAGE_PROCESSOR_HELPER_H_
#include <string_view>

void Helper();

void WrongFilter(std::string_view filter_name);

void Exception(std::exception& exception);

#endif
