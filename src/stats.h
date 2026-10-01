#pragma once

#include <vector>

#include "student.h"

void printHistogram(const std::vector<Student>& students);
void printSubjectHistogram(const std::vector<Student>& students, int subject);
double classAverage(const std::vector<Student>& students);
void printSubjectReport(const std::vector<Student>& students);
