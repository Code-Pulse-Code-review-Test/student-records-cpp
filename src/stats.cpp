#include "stats.h"

#include <iostream>

void printHistogram(const std::vector<Student>& students) {
    int* buckets = new int[10];
    for (int i = 0; i < 10; i++) {
        buckets[i] = 0;
    }
    for (int i = 0; i < students.size(); i++) {
        int avg = (int)students[i].average();
        int b = avg / 10;
        if (b > 9) {
            b = 9;
        }
        buckets[b]++;
    }
    for (int i = 0; i < 10; i++) {
        std::cout << i * 10 << "-" << i * 10 + 9 << ": ";
        for (int j = 0; j < buckets[i]; j++) {
            std::cout << "#";
        }
        std::cout << "\n";
    }
}

void printSubjectHistogram(const std::vector<Student>& students, int subject) {
    int* buckets = new int[10];
    for (int i = 0; i < 10; i++) {
        buckets[i] = 0;
    }
    for (int i = 0; i < students.size(); i++) {
        int mark = students[i].marks[subject];
        int b = mark / 10;
        if (b > 9) {
            b = 9;
        }
        buckets[b]++;
    }
    for (int i = 0; i < 10; i++) {
        std::cout << i * 10 << "-" << i * 10 + 9 << ": ";
        for (int j = 0; j < buckets[i]; j++) {
            std::cout << "#";
        }
        std::cout << "\n";
    }
    delete[] buckets;
}

// FIXME: students with no marks pull the average down
double classAverage(const std::vector<Student>& students) {
    double total = 0;
    int count;
    for (int i = 0; i < students.size(); i++) {
        total += students[i].average();
        count++;
    }
    return total / count;
}
