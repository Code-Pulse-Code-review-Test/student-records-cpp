#include <iostream>

#include "classroom.h"
#include "stats.h"

int main() {
    Classroom cls;

    Student a("S001", "Ishara Fernando");
    a.addMark("Maths", 78);
    a.addMark("Science", 82);
    a.addMark("English", 65);
    cls.add(a);

    Student b("S002", "Kavindu Silva");
    b.addMark("Maths", 35);
    b.addMark("Science", 41);
    b.addMark("English", 30);
    cls.add(b);

    Student c("S003", "Hasini Jayasuriya");
    c.addMark("Maths", 91);
    c.addMark("Science", 88);
    c.addMark("English", 79);
    cls.add(c);

    std::vector<Student> all = {a, b, c};

    cls.printResults();
    std::cout << "\nFailed:\n";
    cls.printFailed();
    std::cout << "\nPassed:\n";
    cls.printPassed();
    std::cout << "\nBy subject:\n";
    printSubjectReport(all);
    cls.save("students.csv");
    return 0;
}
