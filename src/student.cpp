#include "student.h"

Student::Student(std::string id, std::string name) : id(id), name(name) {}

void Student::addMark(std::string subject, int mark) {
    subjects.push_back(subject);
    marks.push_back(mark);
}

double Student::average() const {
    if (marks.empty()) {
        return 0;
    }
    int total = 0;
    for (int m : marks) {
        total += m;
    }
    return (double)total / marks.size();
}

int Student::best() const {
    int best = 0;
    for (int m : marks) {
        if (m > best) {
            best = m;
        }
    }
    return best;
}

std::string Student::grade() const {
    double avg = average();
    if (avg >= 75) return "A";
    if (avg >= 65) return "B";
    if (avg >= 55) return "C";
    if (avg >= 40) return "S";
    return "F";
}
