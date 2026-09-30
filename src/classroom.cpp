#include "classroom.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace {

const char* const kRule = "----------------------------------------------\n";

void printHeader() {
    std::cout << std::left << std::setw(8) << "ID" << std::setw(20) << "Name" << std::setw(8) << "Avg"
              << std::setw(6) << "Grade" << "Rank\n";
    std::cout << kRule;
}

void printRow(const Student& s) {
    std::cout << std::left << std::setw(8) << s.id << std::setw(20) << s.name << std::setw(8)
              << std::fixed << std::setprecision(1) << s.average() << std::setw(6) << s.grade() << s.rank
              << "\n";
}

}  // namespace

void Classroom::add(const Student& s) {
    students.push_back(s);
}

Student* Classroom::find(const std::string& id) {
    for (Student& s : students) {
        if (s.id == id) {
            return &s;
        }
    }
    return nullptr;
}

void Classroom::rankStudents() {
    std::vector<Student*> sorted;
    for (auto& s : students) {
        sorted.push_back(&s);
    }
    std::sort(sorted.begin(), sorted.end(), [](Student* a, Student* b) { return a->average() > b->average(); });
    for (std::size_t i = 0; i < sorted.size(); i++) {
        sorted[i]->rank = static_cast<int>(i) + 1;
    }
}

void Classroom::printTable(const std::function<bool(const Student&)>& include) {
    rankStudents();
    printHeader();
    for (const Student& s : students) {
        if (include(s)) {
            printRow(s);
        }
    }
    std::cout << kRule;
}

void Classroom::printResults() {
    printTable([](const Student&) { return true; });
}

void Classroom::printFailed() {
    printTable([](const Student& s) { return s.grade() == "F"; });
}

void Classroom::printPassed() {
    printTable([](const Student& s) { return s.grade() != "F"; });
}

// one line per student: id,name,subject:mark,subject:mark
void Classroom::save(const std::string& file) {
    std::ofstream out(file);
    for (const Student& s : students) {
        out << s.id << "," << s.name;
        for (std::size_t i = 0; i < s.marks.size(); i++) {
            out << "," << s.subjects[i] << ":" << s.marks[i];
        }
        out << "\n";
    }
}

// older files only have the marks, those subjects get numbered names
void Classroom::load(const std::string& file) {
    std::ifstream in(file);
    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string id, name, field;
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        Student s(id, name);
        int n = 1;
        while (std::getline(ss, field, ',')) {
            const std::size_t colon = field.find(':');
            if (colon == std::string::npos) {
                s.addMark("Subject " + std::to_string(n), std::stoi(field));
            } else {
                s.addMark(field.substr(0, colon), std::stoi(field.substr(colon + 1)));
            }
            n++;
        }
        students.push_back(s);
    }
}
