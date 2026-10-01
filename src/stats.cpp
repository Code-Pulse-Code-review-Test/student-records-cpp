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
