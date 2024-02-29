#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>

struct Student {
    std::string Vardas;
    std::string Pavarde;
    int n;
    std::vector<double> nd;
    double egz;
    double galutinis;
    double galutinisMed;
    double vidurkis;
};

std::vector<Student> Studentai;

void inputStudentInfo(Student& student);
void inputGrades(Student& student);
void inputExamResult(Student& student);
void calculateResults(Student& student, int calculationMethod);

#endif
