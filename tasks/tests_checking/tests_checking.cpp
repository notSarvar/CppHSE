#include "tests_checking.h"

#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string_view> checking_line;
    for (const auto& i : student_actions) {
        if (i.side == Side::Top) {
            checking_line.push_front(i.name);
        } else {
            checking_line.push_back(i.name);
        }
    }
    std::vector<std::string_view> students_order;
    for (const auto& i : queries) {
        students_order.push_back(checking_line[i - 1]);
    }
    return {students_order.begin(), students_order.end()};
}
