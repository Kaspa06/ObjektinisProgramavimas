#include <iostream>
#include <string>
#include <iomanip>
#include <list>
#include <numeric>
#include <algorithm>
#include <cmath>
#include "funkcijosList.h"
#include "studentas.h"
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

void rusiuotiList1(const std::list<int>& sizes) {
    for (auto it = sizes.begin(); it != sizes.end(); ++it) {
        std::string fileName = "studentai" + std::to_string(*it) + ".txt";
        std::ifstream inFile(fileName);

        if (!inFile) {
            std::cerr << "Nepavyko atidaryti failo: " << fileName << std::endl;
            continue;
        }

        std::list<Studentas> studentai, kietiakiai, vargsiukai;
        Studentas tempStudentas;
        std::string eilute;
        std::getline(inFile, eilute); 

        auto startRead = std::chrono::high_resolution_clock::now();

        while (std::getline(inFile, eilute)) {
            std::istringstream eiluteStream(eilute);
            eiluteStream >> tempStudentas.vardas >> tempStudentas.pavarde;
            tempStudentas.nd.clear();
            int pazymys;

            while (eiluteStream >> pazymys) {
                tempStudentas.nd.push_back(pazymys);
            }
            
            if (!tempStudentas.nd.empty()) {
                tempStudentas.egzaminas = tempStudentas.nd.back();
                tempStudentas.nd.pop_back();
            }

            studentai.push_back(tempStudentas);
        }

        inFile.close();

        auto endRead = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedRead = endRead - startRead;
        std::cout << "Duomenu nuskaitymas is " << fileName << " uztruko: " << elapsedRead.count() << " sekundziu." << std::endl;

        for (const auto& studentas : studentai) {
            double galutinisBalas = 0.4 * vidurkis(studentas.nd) + 0.6 * studentas.egzaminas;
            if (galutinisBalas < 5.0) {
                vargsiukai.push_back(studentas);
            } else {
                kietiakiai.push_back(studentas);
            }
        }
        std::ofstream kietiakiaiFile("kietiakiai.txt"), vargsiukaiFile("vargsiukai.txt");

        for (const auto &studentas : kietiakiai) {
            kietiakiaiFile << studentas.vardas << " " << studentas.pavarde << " " << std::fixed << std::setprecision(2) << (0.4 * vidurkis(studentas.nd) + 0.6 * studentas.egzaminas) << std::endl;
        }

        for (const auto &studentas : vargsiukai) {
            vargsiukaiFile << studentas.vardas << " " << studentas.pavarde << " " << std::fixed << std::setprecision(2) << (0.4 * vidurkis(studentas.nd) + 0.6 * studentas.egzaminas) << std::endl;
        }

        kietiakiaiFile.close();
        vargsiukaiFile.close();
    }
}

void rusiuotiList2(const std::list<int>& sizes) {
    for (const auto& size : sizes) {
        std::string fileName = "studentai" + std::to_string(size) + ".txt";
        std::ifstream inFile(fileName);

        if (!inFile) {
            std::cerr << "Nepavyko atidaryti failo: " << fileName << std::endl;
            continue;
        }

        std::list<Studentas> studentai, vargsiukai;
        Studentas tempStudentas;
        std::string eilute;
        std::getline(inFile, eilute); 

        auto startRead = std::chrono::high_resolution_clock::now();

        while (std::getline(inFile, eilute)) {
            std::istringstream eiluteStream(eilute);
            eiluteStream >> tempStudentas.vardas >> tempStudentas.pavarde;
            tempStudentas.nd.clear();
            int pazymys;

            while (eiluteStream >> pazymys) {
                tempStudentas.nd.push_back(pazymys);
            }
            
            if (!tempStudentas.nd.empty()) {
                tempStudentas.egzaminas = tempStudentas.nd.back();
                tempStudentas.nd.pop_back();
            }

            studentai.emplace_back(std::move(tempStudentas)); // Use move semantics
        }

        inFile.close();

        auto endRead = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedRead = endRead - startRead;
        std::cout << "Duomenu nuskaitymas is " << fileName << " uztruko: " << elapsedRead.count() << " sekundziu." << std::endl;

        for (auto it = studentai.begin(); it != studentai.end(); ) {
            double galutinisBalas = 0.4 * vidurkis(it->nd) + 0.6 * it->egzaminas;
            if (galutinisBalas < 5.0) {
                vargsiukai.push_back(std::move(*it)); // Use move semantics
                it = studentai.erase(it);
            } else {
                ++it;
            }
        }

        std::ofstream vargsiukaiFile("vargsiukai.txt");

        for (auto& studentas : vargsiukai) {
            double galutinisBalas = 0.4 * vidurkis(studentas.nd) + 0.6 * studentas.egzaminas;
            vargsiukaiFile << studentas.vardas << " " << studentas.pavarde << " " << std::fixed << std::setprecision(2) << galutinisBalas << std::endl; 
        }

        vargsiukaiFile.close();

        std::ofstream outFile(fileName);

        for (auto& studentas : studentai) {
            double galutinisBalas = 0.4 * vidurkis(studentas.nd) + 0.6 * studentas.egzaminas;
            outFile << studentas.vardas << " " << studentas.pavarde << " " << std::fixed << std::setprecision(2) << galutinisBalas << std::endl; 
        }

        outFile.close();
    }
}

void rusiuotiList3(const std::list<int>& sizes) {
    for (auto it = sizes.begin(); it != sizes.end(); ++it) {
        std::string fileName = "studentai" + std::to_string(*it) + ".txt";
        std::ifstream inFile(fileName);

               if (!inFile) {
            std::cerr << "Nepavyko atidaryti failo: " << fileName << std::endl;
            continue;
        }

        std::list<Studentas> studentai;
        Studentas tempStudentas;
        std::string eilute;
        std::getline(inFile, eilute); 

        auto startRead = std::chrono::high_resolution_clock::now();

        while (std::getline(inFile, eilute)) {
            std::istringstream eiluteStream(eilute);
            eiluteStream >> tempStudentas.vardas >> tempStudentas.pavarde;
            tempStudentas.nd.clear();
            int pazymys;

            while (eiluteStream >> pazymys) {
                tempStudentas.nd.push_back(pazymys);
            }
            
            if (!tempStudentas.nd.empty()) {
                tempStudentas.egzaminas = tempStudentas.nd.back();
                tempStudentas.nd.pop_back();
            }

            studentai.push_back(tempStudentas);
        }

        inFile.close();

        auto endRead = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedRead = endRead - startRead;
        std::cout << "Duomenu nuskaitymas is " << fileName << " uztruko: " << elapsedRead.count() << " sekundziu." << std::endl;

        std::list<Studentas> vargsiukai;

        std::copy_if(studentai.begin(), studentai.end(), std::back_inserter(vargsiukai), [](const Studentas& s) {
            double galutinisBalas = 0.4 * vidurkis(s.nd) + 0.6 * s.egzaminas;
            return galutinisBalas < 5.0;
        });

        studentai.erase(std::remove_if(studentai.begin(), studentai.end(), [](const Studentas& s) {
            double galutinisBalas = 0.4 * vidurkis(s.nd) + 0.6 * s.egzaminas;
            return galutinisBalas < 5.0;
        }), studentai.end());

        std::ofstream vargsiukaiFile("vargsiukai.txt");
        std::ofstream outFile(fileName);

        std::for_each(vargsiukai.begin(), vargsiukai.end(), [&vargsiukaiFile](const Studentas& s) {
            vargsiukaiFile << s.vardas << " " << s.pavarde << " " << std::fixed << std::setprecision(2) << (0.4 * vidurkis(s.nd) + 0.6 * s.egzaminas) << std::endl;
        });

        // Write remaining students to outFile
        std::for_each(studentai.begin(), studentai.end(), [&outFile](const Studentas& s) {
            outFile << s.vardas << " " << s.pavarde << " " << std::fixed << std::setprecision(2) << (0.4 * vidurkis(s.nd) + 0.6 * s.egzaminas) << std::endl;
        });

        vargsiukaiFile.close();
        outFile.close();
    }
}
