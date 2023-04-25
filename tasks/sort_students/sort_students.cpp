#include "sort_students.h"

bool DateComparison(Student st1, Student st2) {
    if (st1.birth_date.year == st2.birth_date.year && st1.birth_date.month == st2.birth_date.month) {
        return st1.birth_date.day < st2.birth_date.day;
    } else if (st1.birth_date.year == st2.birth_date.year) {
        return st1.birth_date.month < st2.birth_date.month;
    } else {
        return st1.birth_date.year < st2.birth_date.year;
    }
}
bool NameComparison(Student st1, Student st2) {
    if (st1.last_name == st2.last_name) {
        return st1.name.compare(st2.name) < 0;
    }
    return st1.last_name.compare(st2.last_name) < 0;
}

bool CompareByDate(Student st1, Student st2) {
    if (st1.birth_date.year == st2.birth_date.year && st1.birth_date.month == st2.birth_date.month &&
        st1.birth_date.day == st2.birth_date.day) {
        return NameComparison(st1, st2);
    }
    return DateComparison(st1, st2);
}
bool CompareByName(Student st1, Student st2) {
    if (st1.last_name == st2.last_name && st1.name == st2.name) {
        return DateComparison(st1, st2);
    }
    return NameComparison(st1, st2);
}

void SortStudents(std::vector<Student>& students, SortKind sort_kind) {
    if (sort_kind == SortKind::Date) {
        std::sort(students.begin(), students.end(), CompareByDate);
    } else {
        std::sort(students.begin(), students.end(), CompareByName);
    }
}
