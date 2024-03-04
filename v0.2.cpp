#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egzaminas;
};

double vidurkis(const vector<int>& nd) {
    if(nd.empty()) return 0.0;
    double suma = 0.0;
    for (int pazymys : nd) {
        suma += pazymys;
    }
    return suma / nd.size();
}

double mediana(vector<int> nd) {
    if(nd.empty()) return 0.0;
    sort(nd.begin(), nd.end());
    size_t dydis = nd.size();
    if (dydis % 2 == 0) {
        return (nd[dydis / 2 - 1] + nd[dydis / 2]) / 2.0;
    } else {
        return nd[dydis / 2];
    }
}

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
        int num1 = stoi(a.pavarde.substr(6));
        int num2 = stoi(b.pavarde.substr(6));
        return num1 > num2;
    }else return a.pavarde > b.pavarde;
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

void PrintData(const vector<Studentas>& studentai, const string& isvedimoFailoVardas = "", int choice = 1){
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
    out << "----------------------------------------------------------------\n";
    out << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)\n";
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

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    vector<Studentas> studentai;
    int pasirinkimas = 0;

    double visoLaikoSuma = 0.0;
    int testuSkaicius = 0;

    vector<double> testuLaikai;

    while (pasirinkimas != 5) {
        auto start = chrono::high_resolution_clock::now();

        cout << "\nMenu:\n";
        cout << "1. Ivesti viska rankomis\n";
        cout << "2. Generuoti pazymius\n";
        cout << "3. Generuoti ir pazymius ir studentu vardus, pavardes\n";
        cout << "4. Gauti studentu vardus, pavardes, pazymius is failo.\n";
        cout << "5. Baigti darba\n";
        cout << "Rinktis (1-5): ";
        cin >> pasirinkimas;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pasirinkimas) {
            case 1:
                manualInput(studentai);
                break;
            case 2:
                generateGradesOnly(studentai);
                break;
            case 3:
                for (int i = 0; i < 5; ++i) {
                    Studentas naujasStudentas;
                    generateRandomNamesAndGrades(naujasStudentas);
                    studentai.push_back(naujasStudentas);
                }
                break;
            case 4:
                {
                    readFileDataFromFile(studentai, pasirinktiFaila());
                    int choice = pasirinktiRusiavimoTipa();
                    PrintData(studentai, "rezultatai.txt", choice);
                    break;
                }
            case 5:
                break;
        }

        if (pasirinkimas != 5) {
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> time = end - start;
            double laikas = time.count();
            cout << "Operacija uztruko: " << laikas << " s" << endl;
            visoLaikoSuma += laikas;
            testuSkaicius++;
        }
    }

    double vidurkis = visoLaikoSuma / testuSkaicius;
    cout << "Keliu testu laiku vidurkis: " << vidurkis << " s" << endl;

    return 0;
}
