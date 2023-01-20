#include "sort_students.h"

#define bd birth_date

bool comp_date(Student& a, Student& b) {
    return tie(a.bd.year, a.bd.month, a.bd.day, a.last_name, a.name) <
           tie(b.bd.year, b.bd.month, b.bd.day, b.last_name, b.name);
}

bool comp_name(Student& a, Student& b) {
    return tie(a.last_name, a.name, a.bd.year, a.bd.month, a.bd.day) <
           tie(b.last_name, b.name, b.bd.year, b.bd.month, b.bd.day);
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if(sortKind == SortKind::Date) {
        std::sort(students.begin(), students.end(), comp_date);
    } else {
        std::sort(students.begin(), students.end(), comp_name);
    }
}
