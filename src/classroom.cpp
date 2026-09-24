#include "classroom.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

void Classroom::add(Student s) {
    students.push_back(s);
}

Student* Classroom::find(std::string id) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            return &students[i];
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
    for (int i = 0; i < sorted.size(); i++) {
        sorted[i]->rank = i + 1;
    }
}

void Classroom::printResults() {
    rankStudents();
    std::cout << std::left << std::setw(8) << "ID" << std::setw(20) << "Name" << std::setw(8) << "Avg"
              << std::setw(6) << "Grade" << "Rank\n";
    std::cout << "----------------------------------------------\n";
    for (int i = 0; i < students.size(); i++) {
        Student& s = students[i];
        std::cout << std::left << std::setw(8) << s.id << std::setw(20) << s.name << std::setw(8)
                  << std::fixed << std::setprecision(1) << s.average() << std::setw(6) << s.grade() << s.rank
                  << "\n";
    }
    std::cout << "----------------------------------------------\n";
}

void Classroom::printFailed() {
    rankStudents();
    std::cout << std::left << std::setw(8) << "ID" << std::setw(20) << "Name" << std::setw(8) << "Avg"
              << std::setw(6) << "Grade" << "Rank\n";
    std::cout << "----------------------------------------------\n";
    for (int i = 0; i < students.size(); i++) {
        Student& s = students[i];
        if (s.grade() != "F") continue;
        std::cout << std::left << std::setw(8) << s.id << std::setw(20) << s.name << std::setw(8)
                  << std::fixed << std::setprecision(1) << s.average() << std::setw(6) << s.grade() << s.rank
                  << "\n";
    }
    std::cout << "----------------------------------------------\n";
}

void Classroom::printPassed() {
    rankStudents();
    std::cout << std::left << std::setw(8) << "ID" << std::setw(20) << "Name" << std::setw(8) << "Avg"
              << std::setw(6) << "Grade" << "Rank\n";
    std::cout << "----------------------------------------------\n";
    for (int i = 0; i < students.size(); i++) {
        Student& s = students[i];
        if (s.grade() == "F") continue;
        std::cout << std::left << std::setw(8) << s.id << std::setw(20) << s.name << std::setw(8)
                  << std::fixed << std::setprecision(1) << s.average() << std::setw(6) << s.grade() << s.rank
                  << "\n";
    }
    std::cout << "----------------------------------------------\n";
}

// TODO: save subject names too, only marks are written now
void Classroom::save(std::string file) {
    std::ofstream out(file);
    for (auto& s : students) {
        out << s.id << "," << s.name;
        for (int m : s.marks) {
            out << "," << m;
        }
        out << "\n";
    }
}

void Classroom::load(std::string file) {
    std::ifstream in(file);
    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string id, name, mark;
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        Student s(id, name);
        int n = 1;
        while (std::getline(ss, mark, ',')) {
            s.addMark("Subject " + std::to_string(n), std::stoi(mark));
            n++;
        }
        students.push_back(s);
    }
}
