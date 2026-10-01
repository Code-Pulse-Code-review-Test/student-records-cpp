#include "stats.h"

#include <array>
#include <iostream>
#include <string>

namespace {

using Buckets = std::array<int, 10>;

// 0-9, 10-19, ... and 90-100 share the last bucket
int bucketFor(double value) {
    int b = static_cast<int>(value) / 10;
    if (b > 9) {
        b = 9;
    }
    if (b < 0) {
        b = 0;
    }
    return b;
}

void printBuckets(const Buckets& buckets) {
    for (int i = 0; i < 10; i++) {
        std::cout << i * 10 << "-" << i * 10 + 9 << ": " << std::string(buckets[i], '#') << "\n";
    }
}

}  // namespace

void printHistogram(const std::vector<Student>& students) {
    Buckets buckets{};
    for (const Student& s : students) {
        buckets[bucketFor(s.average())]++;
    }
    printBuckets(buckets);
}

void printSubjectHistogram(const std::vector<Student>& students, int subject) {
    Buckets buckets{};
    for (const Student& s : students) {
        // not every student has a mark for every subject
        if (subject < 0 || subject >= static_cast<int>(s.marks.size())) {
            continue;
        }
        buckets[bucketFor(s.marks[subject])]++;
    }
    printBuckets(buckets);
}

// students with no marks yet are left out
double classAverage(const std::vector<Student>& students) {
    double total = 0;
    int count = 0;
    for (const Student& s : students) {
        if (s.marks.empty()) {
            continue;
        }
        total += s.average();
        count++;
    }
    if (count == 0) {
        return 0;
    }
    return total / count;
}

void printSubjectReport(const std::vector<Student>& students) {
    if (students.empty()) {
        return;
    }
    const std::vector<std::string>& subjects = students[0].subjects;
    for (int i = 0; i < (int)subjects.size(); i++) {
        double total = 0;
        int count = 0;
        int top = -1;
        std::string topName = "";
        for (int j = 0; j < (int)students.size(); j++) {
            if (i < (int)students[j].marks.size()) {
                total += students[j].marks[i];
                count++;
                if (students[j].marks[i] > top) {
                    top = students[j].marks[i];
                    topName = students[j].name;
                }
            }
        }
        int low = 101;
        std::string lowName = "";
        for (int j = 0; j < (int)students.size(); j++) {
            if (i < (int)students[j].marks.size()) {
                if (students[j].marks[i] < low) {
                    low = students[j].marks[i];
                    lowName = students[j].name;
                }
            }
        }
        int passed = 0;
        int failed = 0;
        for (int j = 0; j < (int)students.size(); j++) {
            if (i < (int)students[j].marks.size()) {
                if (students[j].marks[i] >= 40) {
                    passed++;
                } else {
                    failed++;
                }
            }
        }
        std::cout << subjects[i] << "\n";
        if (count > 0) {
            std::cout << "  Average: " << total / count << "\n";
        }
        std::cout << "  Top: " << topName << " (" << top << ")\n";
        std::cout << "  Lowest: " << lowName << " (" << low << ")\n";
        std::cout << "  Passed: " << passed << " Failed: " << failed << "\n";
        if (failed > passed) {
            std::cout << "  ** more than half failed **\n";
        } else if (failed * 4 > passed) {
            std::cout << "  * check this subject *\n";
        }
    }
}
