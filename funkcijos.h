#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "studentas.h"

std::string pasirinktiFaila();
int pasirinktiRusiavimoTipa();
void PrintData(const std::vector<Studentas>& studentai, const std::string& isvedimoFailoVardas = "", int choice = 1);
void manualInput(std::vector<Studentas>& studentai);
void generateGradesOnly(std::vector<Studentas>& studentai);
void readFileDataFromFile(std::vector<Studentas>& studentai, const std::string& failoVardas);
void generateStudentFiles(const std::vector<int>& sizes);
void processChunk(std::vector<Studentas>& studentai);
void rusiuotiStudentus(const std::vector<int>& sizes);

#endif
