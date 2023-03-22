#include "imagework.h"
#include "parser.h"
#include "helper.h"
#include "filtersmanager.h"

int main(int argc, char** argv) {
    Parser input;
    if (!input.Parse(argc, argv)) {
        Helper();
        return 1;
    }

    Image cur_image(input.GetInputFileName());

    auto filter_applicator = FilterApplicator();

    for (const FilterDescription& description : input.filters_to_apply) {
        auto filter_generator = filter_applicator.ApplyFilter(description.name);
        if (filter_generator == nullptr) {
            WrongFilter(description.name);
            return 1;
        }

        BaseFilter* filter = filter_generator(description);

        filter->Apply(cur_image);
        delete filter;
    }

    cur_image.WriteBMP(input.GetOutputFileName());

    return 0;
}
