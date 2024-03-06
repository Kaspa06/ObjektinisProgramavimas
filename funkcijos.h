#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "studentas.h"
#include <vector>
#include <string>

std::string pasirinktiFaila();
int pasirinktiRusiavimoTipa();
void PrintData(const std::vector<Studentas>& studentai, const std::string& isvedimoFailoVardas = "", int choice = 1);
void manualInput(std::vector<Studentas>& studentai);
void generateGradesOnly(std::vector<Studentas>& studentai);
void readFileDataFromFile(std::vector<Studentas>& studentai, const std::string& failoVardas);

#endif
