#pragma once

#include <functional>
#include <string>
#include <vector>

#include "student.h"

class Classroom {
public:
    void add(const Student& s);
    Student* find(const std::string& id);
    void rankStudents();
    void printResults();
    void printFailed();
    void printPassed();
    void save(const std::string& file);
    void load(const std::string& file);

private:
    std::vector<Student> students;

    void printTable(const std::function<bool(const Student&)>& include);
};
