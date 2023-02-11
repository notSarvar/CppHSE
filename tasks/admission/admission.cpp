#include "admission.h"

#include <tuple>

bool ApplicantComp(const Applicant* a, const Applicant* b) {
    if (a->points > b->points) {
        return true;
    } else if (a->points == b->points) {
        return std::tie(a->student.birth_date.year, a->student.birth_date.month, a->student.birth_date.day,
                        a->student.name) < std::tie(b->student.birth_date.year, b->student.birth_date.month,
                                                    b->student.birth_date.day, b->student.name);
    }
    return false;
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> sorted_applicants;
    for (const auto& i : applicants) {
        sorted_applicants.push_back(&i);
    }
    std::sort(sorted_applicants.begin(), sorted_applicants.end(), ApplicantComp);

    std::unordered_map<std::string, std::size_t> unis_max_students;
    for (const auto& i : universities) {
        unis_max_students[i.name] = i.max_students;
    }

    AdmissionTable admission_table;
    for (const auto& i : sorted_applicants) {
        for (const auto& j : i->wish_list) {
            if (unis_max_students[j]) {
                --unis_max_students[j];
                admission_table[j].push_back(&i->student);
                break;
            }
        }
    }

    return admission_table;
}
