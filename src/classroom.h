#pragma once

#include <string>
#include <vector>

#include "student.h"

class Classroom {
public:
    void add(Student s);
    Student* find(std::string id);
    void rankStudents();
    void printResults();
    void printFailed();
    void printPassed();
    void save(std::string file);
    void load(std::string file);

private:
    std::vector<Student> students;
};
