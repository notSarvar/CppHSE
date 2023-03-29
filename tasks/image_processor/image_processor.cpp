#include "imagework.h"
#include "parser.h"
#include "helper.h"
#include "filtersmanager.h"

int main(int argc, char** argv) {
    Parser input;
    if (!input.Parse(argc, argv)) {
        WrongInputParams();
    }

    Image cur_image(input.GetInputFileName());

    FilterApplicator filter_to_get;

    for (const FilterDescription& description : input.filters_to_apply) {
        auto filter_to_apply = filter_to_get.GetFilter(description.name);
        if (filter_to_apply == nullptr) {
            WrongFilter(description.name);
        }

        BaseFilter* filter = filter_to_apply(description);

        filter->Apply(cur_image);
        delete filter;
    }

    cur_image.WriteBMP(input.GetOutputFileName());

    return 0;
}
