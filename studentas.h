#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    int egzaminas;
};

double vidurkis(const std::vector<int>& nd);
double mediana(std::vector<int> nd);
void generateRandomGrades(Studentas& studentas);
void generateRandomNamesAndGrades(Studentas& studentas);

#endif
