#include "tests_checking.h"

#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> order;
    std::vector<std::string> students;
    for (size_t i = 0; i < student_actions.size(); ++i) {
        student_actions[i].side == Side::Top ? order.push_front(student_actions[i].name)
                                             : order.push_back(student_actions[i].name);
    }
    for (size_t i = 0; i < queries.size(); ++i) {
        students.push_back(order[queries[i] - 1]);
    }
    return students;
}
