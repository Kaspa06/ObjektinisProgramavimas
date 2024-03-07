#include "funkcijos.h"
#include "studentas.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>

using namespace std;

bool sortByVardas(const Studentas& a, const Studentas& b) {
    if (a.vardas.find("Vardas") == 0 && b.vardas.find("Vardas") == 0) {
        try {
            int num1 = stoi(a.vardas.substr(6));
            int num2 = stoi(b.vardas.substr(6));
            return num1 > num2;
        } catch (const std::invalid_argument&) {
            return a.vardas > b.vardas;
        }
    } else {
        return a.vardas > b.vardas;
    }
}

bool sortByPavarde(const Studentas& a, const Studentas& b) {
    if (a.pavarde.find("Pavarde") == 0 && b.pavarde.find("Pavarde") == 0) {
        try {
        int num1 = stoi(a.pavarde.substr(6));
        int num2 = stoi(b.pavarde.substr(6));
        return num1 > num2;
        } catch (const std::invalid_argument&) {
            return a.vardas > b.vardas;
        }
    }else {
        return a.pavarde > b.pavarde;
    }
}

bool sortByVidurkis(const Studentas& a, const Studentas& b) {
    double vidurkisA = 0.4 * vidurkis(a.nd) + 0.6 * a.egzaminas;
    double vidurkisB = 0.4 * vidurkis(b.nd) + 0.6 * b.egzaminas;
    return vidurkisA < vidurkisB;
}

bool sortByMediana(const Studentas& a, const Studentas& b) {
    double medianaA = 0.4 * mediana(a.nd) + 0.6 * a.egzaminas;
    double medianaB = 0.4 * mediana(b.nd) + 0.6 * b.egzaminas;
    return medianaA < medianaB;
}

void PrintData(const vector<Studentas>& studentai, const string& isvedimoFailoVardas, int choice){
    ostream& out = isvedimoFailoVardas.empty() ? cout : *new ofstream(isvedimoFailoVardas);
    vector<Studentas> SortedStudents = studentai;

    switch (choice) {
        case 1:
            sort(SortedStudents.begin(), SortedStudents.end(), sortByVardas);
            break;
        case 2:
            sort(SortedStudents.begin(), SortedStudents.end(), sortByPavarde);
            break;
        case 3:
            sort(SortedStudents.begin(), SortedStudents.end(), sortByVidurkis);
            break;
        case 4:
            sort(SortedStudents.begin(), SortedStudents.end(), sortByMediana);
            break;
    }

    out << fixed << setprecision(2);
    out << "----------------------------------------------------------------\n"<<endl;
    out << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)\n"<<endl;
    out << "----------------------------------------------------------------\n";

    for (const Studentas& studentas : SortedStudents) {
        double galutinisVidurkis = 0.4 * vidurkis(studentas.nd) + 0.6 * studentas.egzaminas;
        double galutineMediana = 0.4 * mediana(studentas.nd) + 0.6 * studentas.egzaminas;
        out << left << setw(15) << studentas.vardas << setw(15) << studentas.pavarde << setw(20) << galutinisVidurkis << setw(20) << galutineMediana << "\n";
    }
    out << "----------------------------------------------------------------\n";

    if (!isvedimoFailoVardas.empty()) {
        delete &out; 
    }
}

void manualInput(vector<Studentas>& studentai) {
    char testi = 't';

    while (testi == 't') {
        Studentas naujasStudentas;

        cout << "Iveskite studento varda: ";
        getline(cin, naujasStudentas.vardas);

        cout << "Iveskite studento pavarde: ";
        getline(cin, naujasStudentas.pavarde);

        int pazymys;
        cout << "Iveskite namu darbu pazymius (0 norint baigti): ";
        while (cin >> pazymys && pazymys != 0) {
            naujasStudentas.nd.push_back(pazymys);
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Iveskite egzamino rezultata: ";
        cin >> naujasStudentas.egzaminas;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        studentai.push_back(naujasStudentas);

        cout << "Ar norite ivesti dar viena studenta? (t/n): ";
        cin >> testi;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    PrintData(studentai, "rezultatai.txt", 1);
}

void generateGradesOnly(vector<Studentas>& studentai) {
    for (Studentas& studentas : studentai) {
        studentas.nd.clear();
        int ndKiekis = rand() % 10 + 1;
        for (int i = 0; i < ndKiekis; ++i) {
            studentas.nd.push_back(rand() % 10 + 1);
        }
        studentas.egzaminas = rand() % 10 + 1;
    }
    PrintData(studentai, "rezultatai.txt", 1);
}

void readFileDataFromFile(vector<Studentas>& studentai, const string&failoVardas){
    ifstream failas(failoVardas);
    if (!failas.is_open()) {
        cerr << "Nepavyko atidaryti failo: " << failoVardas << endl;
        return;
    }

    Studentas studentas;
    string eilute;
    getline(failas, eilute);

     while (getline(failas, eilute)) {
        istringstream eilutesSrautas(eilute);
        eilutesSrautas >> studentas.vardas >> studentas.pavarde;

        int pazymys;
        studentas.nd.clear();
        while (eilutesSrautas >> pazymys && pazymys != -1) {
            studentas.nd.push_back(pazymys);
        }

        studentas.egzaminas = pazymys;
        studentai.push_back(studentas);
    }

    failas.close();
}

string pasirinktiFaila()
{
    system("dir *.txt");

    string fileName;
    cout << "Enter the file name to read data from: ";
    cin >> fileName;

    return fileName;
}

int pasirinktiRusiavimoTipa() {
    cout << "Pasirinkite rusiavimo buda:\n"
         << "1 - Pagal varda\n"
         << "2 - Pagal pavarde\n"
         << "3 - Pagal vidurki\n"
         << "4 - Pagal mediana\n"
         << "Iveskite pasirinkima: ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}
void generateStudentFiles(const std::vector<int> &sizes)
{
    for (int size : sizes)
    {
        std::string fileName = "studentai" + std::to_string(size) + ".txt";
        std::ofstream outFile(fileName);

        outFile << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde";
        for (int i = 1; i <= 15; ++i)
        {
            outFile << std::setw(10) << "ND" + std::to_string(i);
        }
        outFile << std::setw(10) << "Egz." << std::endl;

        for (int i = 1; i <= size; i++)
        {
            outFile << std::left << std::setw(15) << "Vardas" + std::to_string(i)
                    << std::setw(15) << "Pavarde" + std::to_string(i);
            for (int j = 0; j < 15; j++)
            {
                outFile << std::setw(10) << (rand() % 10 + 1);
            }
            outFile << std::setw(10) << (rand() % 10 + 1);
            outFile << std::endl;
        }

        outFile.close();
    }
}

void rusiuotiStudentus(const std::vector<int>& sizes) {
    for (size_t index = 0; index < sizes.size(); ++index) {
        std::string fileName = "studentai" + std::to_string(sizes[index]) + ".txt";
        std::ifstream inFile(fileName);

        if (!inFile) {
            std::cerr << "Nepavyko atidaryti failo: " << fileName << std::endl;
            continue;
        }

        std::vector<Studentas> studentai, kietiakiai, vargsiukai;
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

        auto startSort = std::chrono::high_resolution_clock::now();

        for (const auto& studentas : studentai) {
            double galutinisBalas = 0.4 * vidurkis(studentas.nd) + 0.6 * studentas.egzaminas;
            if (galutinisBalas < 5.0) {
                vargsiukai.push_back(studentas);
            } else {
                kietiakiai.push_back(studentas);
            }
        }

        auto endSort = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedSort = endSort - startSort;
        std::cout << "Studentu rusiavimas uztruko: " << elapsedSort.count() << " sekundziu." << std::endl;

        // Isvedimas i failus
        std::ofstream kietiakiaiFile("kietiakiai.txt"), vargsiukaiFile("vargsiukai.txt");

        for (const auto &studentas : kietiakiai) {
            kietiakiaiFile << studentas.vardas << " " << studentas.pavarde << " " << std::fixed << std::setprecision(2) << (0.4 * vidurkis(studentas.nd) + 0.6 * studentas.egzaminas) << std::endl;
        }

        for (const auto &studentas : vargsiukai) {
            vargsiukaiFile << studentas.vardas << " " << studentas.pavarde << " " << std::fixed << std::setprecision(2) << (0.4 * vidurkis(studentas.nd) + 0.6 * studentas.egzaminas) << std::endl;
        }

        kietiakiaiFile.close();
        vargsiukaiFile.close();

        std::cout << "Studentai is " << fileName << " buvo sekmingai isrusiuoti ir issaugoti i atitinkamus failus." << std::endl;
    }
}
