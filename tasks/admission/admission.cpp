#include "admission.h"

#include <algorithm>
#include <iostream>

bool operator!=(const Date& date1, const Date& date2);

bool DateComparison(Student st1, Student st2);

bool CompareApplicants(const Applicant* first, const Applicant* second);

std::vector<const Applicant*> SortApplicants(const std::vector<Applicant>& applicants);

void Enroll(const Applicant* applicant, const std::vector<University>& universities, AdmissionTable& table);

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    AdmissionTable table;
    std::vector<const Applicant*> sorted_applicants = SortApplicants(applicants);
    for (const Applicant* applicant : sorted_applicants) {
        Enroll(applicant, universities, table);
    }
    return table;
}

std::vector<const Applicant*> SortApplicants(const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> applicants_pointers;
    for (int i = 0; i < static_cast<int>(applicants.size()); ++i) {
        applicants_pointers.push_back(&applicants[i]);
    }
    std::sort(applicants_pointers.begin(), applicants_pointers.end(), CompareApplicants);
    return applicants_pointers;
}

void Enroll(const Applicant* applicant, const std::vector<University>& universities, AdmissionTable& table) {
    for (const std::string& university_name : applicant->wish_list) {
        bool is_enrolled = false;
        for (University university : universities) {
            if (university_name == university.name && university.max_students > table[university_name].size()) {
                --university.max_students;
                table[university_name].push_back(&applicant->student);
                is_enrolled = true;
                break;
            }
        }
        if (is_enrolled) {
            break;
        }
    }
}

bool operator!=(const Date& date1, const Date& date2) {
    return !(date1.year == date2.year && date1.month == date2.month && date1.day == date2.day);
}

bool DateComparison(Student st1, Student st2) {
    if (st1.birth_date.year == st2.birth_date.year && st1.birth_date.month == st2.birth_date.month) {
        return st1.birth_date.day < st2.birth_date.day;
    } else if (st1.birth_date.year == st2.birth_date.year) {
        return st1.birth_date.month < st2.birth_date.month;
    } else {
        return st1.birth_date.year < st2.birth_date.year;
    }
}

bool CompareApplicants(const Applicant* first, const Applicant* second) {
    if (first->points != second->points) {
        return first->points > second->points;
    } else if (first->student.birth_date != second->student.birth_date) {
        return DateComparison(first->student, second->student);
    }
    return first->student.name < second->student.name;
}
