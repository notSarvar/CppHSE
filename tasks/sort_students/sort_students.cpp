#include "sort_students.h"
#include <tuple>

bool ByDate(Student& a, Student& b) {
    return std::tie(a.birth_date.year, a.birth_date.month, a.birth_date.day, a.last_name, a.name) <
           std::tie(b.birth_date.year, b.birth_date.month, b.birth_date.day, b.last_name, b.name);
}

bool ByName(Student& a, Student& b) {
    return std::tie(a.last_name, a.name, a.birth_date.year, a.birth_date.month, a.birth_date.day) <
           std::tie(b.last_name, b.name, b.birth_date.year, b.birth_date.month, b.birth_date.day);
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    std::sort(students.begin(), students.end(), (sortKind == SortKind::Date) ? ByDate: ByName);
}
