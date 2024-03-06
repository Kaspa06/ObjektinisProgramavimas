#include "studentas.h"
#include <algorithm>
#include <numeric>

double vidurkis(const std::vector<int>& nd) {
    if(nd.empty()) return 0.0;
    double suma = 0.0;
    for (int pazymys : nd) {
        suma += pazymys;
    }
    return suma / nd.size();
}

double mediana(std::vector<int> nd) {
    if(nd.empty()) return 0.0;
    std::sort(nd.begin(), nd.end());
    size_t dydis = nd.size();
    if (dydis % 2 == 0) {
        return (nd[dydis / 2 - 1] + nd[dydis / 2]) / 2.0;
    } else {
        return nd[dydis / 2];
    }
}

void generateRandomGrades(Studentas& studentas) {
    studentas.nd.resize(rand() % 10 + 1);
    for (int& grade : studentas.nd) {
        grade = rand() % 10 + 1;
    }
    studentas.egzaminas = rand() % 10 + 1;
}

void generateRandomNamesAndGrades(Studentas& studentas) {
    const char* vardai[] = {"Jonas", "Petras", "Ona", "Maryte", "Antanas", "Jurga", "Kazys", "Rasa", "Darius", "Aiste"};
    const char* pavardes[] = {"Jonaitis", "Petraitis", "Onute", "Marytiene", "Antanaitis", "Jurgaite", "Kaziukas", "Rasiene", "Dariukas", "Aistyte"};
    int vardasIndex = rand() % 5;
    int pavardeIndex = rand() % 5;
    studentas.vardas = vardai[vardasIndex];
    studentas.pavarde = pavardes[pavardeIndex];
    generateRandomGrades(studentas);
}
