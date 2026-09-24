#pragma once

#include <string>
#include <vector>

class Student {
public:
    Student(std::string id, std::string name);

    void addMark(std::string subject, int mark);
    double average() const;
    int best() const;
    std::string grade() const;

    std::string id;
    std::string name;
    std::vector<std::string> subjects;
    std::vector<int> marks;
    int rank;
};
