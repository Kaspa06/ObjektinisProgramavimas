#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <vector>
#include <limits>
#include <fstream>

using namespace std;

string vardai[] = {"Jonas", "Petras", "Ona", "Maryte", "Antanas", "Jurga", "Kazys", "Rasa", "Darius", "Aiste"};
string pavardes[] = {"Jonaitis", "Petraitis", "Onute", "Marytiene", "Antanaitis", "Jurgaite", "Kaziukas", "Rasiene", "Dariukas", "Aistyte"};

struct Student {
    string Vardas;
    string Pavarde;
    int n;
    vector<double> nd;
    double egz;
    double galutinis;
    double galutinisMed;
    double vidurkis;
};

vector<Student> Studentai;

bool isPositiveInteger(const string& s) {
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

bool isValidDouble(const string& s, double minValue, double maxValue) {
    try {
        double value = stod(s);
        return value >= minValue && value <= maxValue;
    } catch (const invalid_argument&) {
        return false;
    }
}

bool isValidChoice(const string& s) {
    return s == "1" || s == "2" || s == "3" || s == "4";
}

bool isValidGrade(const string& s) {
    if (all_of(s.begin(), s.end(), ::isdigit)) {
        int grade = stoi(s);
        return grade >= 1 && grade <= 10;
    }
    return false;
}

void inputStudentInfo(Student& student) {
    cout << "Iveskite Varda: ";
    cin >> student.Vardas;
    cout << "Iveskite Pavarde: ";
    cin >> student.Pavarde;
}

void inputGrades(Student& student) {
    double sum = 0;
    int j = 0;
    do {
        cout << "Iveskite " << j + 1 << " pazymi (nuo 1 iki 10, arba -1 jei norite baigti): ";
        string gradeInput;
        cin >> gradeInput;

        if (gradeInput == "-1") {
            break;
        }

        if (!isValidGrade(gradeInput)) {
            cout << "Netinkama ivestis. Iveskite skaiciu nuo 1 iki 10." << endl;
        } else {
            student.nd.push_back(stod(gradeInput));
            sum += student.nd[j];
            j++;
        }
    } while (true);

    student.n = j;
    student.vidurkis = sum / student.n;
}

void inputExamResult(Student& student) {
    string egzInput;
    do {
        cout << "Iveskite egzamino rezultata: ";
        cin >> egzInput;
        if (!isValidDouble(egzInput, 1.0, 10.0)) {
            cout << "Netinkama ivestis. Iveskite skaiciu nuo 1 iki 10." << endl;
        }
    } while (!isValidDouble(egzInput, 1.0, 10.0));

    student.egz = stod(egzInput);
}

void calculateResults(Student& student) {
    student.galutinis = 0.4 * student.vidurkis + 0.6 * student.egz;

    int n = student.n;
    student.galutinisMed = (n % 2 == 0) ?
        0.4 * (student.nd[n / 2 - 1] + student.nd[n / 2]) + 0.6 * student.egz :
        0.4 * student.nd[n / 2] + 0.6 * student.egz;
}

void displayTable(int choice) {
    cout << "\nInformacija apie studentus:\n";
    cout << "--------------------------------------------------------------------------------------\n";
    cout << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << (choice == 1 ? "Galutinis(Vid.)" : "Galutinis(med.)") << endl;
    cout << "--------------------------------------------------------------------------------------\n";

    for (const auto& student : Studentai) {
        cout << setw(15) << student.Vardas << setw(15) << student.Pavarde
             << fixed << setprecision(2) << setw(20) << (choice == 1 ? student.galutinis : student.galutinisMed) << endl;
    }
    Studentai.clear();
}

void ChoosePrint()
{
    string choiceInput;
        do {
        cout << "\nKa norite spausdinti: (1 - Galutinis(Vid.), 2 - Galutinis(med.))" << endl;
        cin >> choiceInput;
        if (!isValidChoice(choiceInput)) {
            cout << "Netinkama ivestis. Pasirinkite 1 arba 2." << endl;
        }
    } while (!isValidChoice(choiceInput));

    int choice = stoi(choiceInput);
    displayTable(choice);
}

void inputContinue(string &continueInput) {
    do {
        cout << "Ar norite ivesti kita studenta? (taip/ne): ";
        cin >> continueInput;

        // Convert input to lowercase for case-insensitive comparison
        transform(continueInput.begin(), continueInput.end(), continueInput.begin(), ::tolower);

        if (continueInput == "taip" || continueInput == "ne") {
            break;
        } else if (isdigit(continueInput[0])) {
            // If the input starts with a digit, redirect to the question
            cout << "Netinkama ivestis. Iveskite 'taip' arba 'ne'.\n";
            continue;
        } else {
            cout << "Netinkama ivestis. Iveskite 'taip' arba 'ne'.\n";
        }
    } while (true);
}

void writeEverythingWithHands() {
    do {
        Student student;
        inputStudentInfo(student);
        inputGrades(student);
        inputExamResult(student);
        calculateResults(student);

        Studentai.push_back(student);

        string continueInput;
        inputContinue(continueInput);

        if (continueInput != "taip") {
            break;
        }

    } while (true);

    ChoosePrint();
}

void generateRandomGradeInput() {
    do {
        Student student;
        inputStudentInfo(student);

        int numGrades = rand() % 10 + 1;
        for (int j = 0; j < numGrades; ++j) {
            student.nd.push_back(rand() % 10 + 1);
        }
        student.n = numGrades;

        student.egz = rand() % 10 + 1;

        calculateResults(student);

        Studentai.push_back(student);

        string continueInput;
        inputContinue(continueInput);

        if (continueInput != "taip") {
            break;
        }

    } while (true);

    ChoosePrint();
}

void generateRandomStudentData(int mokiniuSk, int sum) {
    string mokiniuSkInput;
    do {
        cout << "Iveskite kiek bus mokiniu: ";
        cin >> mokiniuSkInput;
        if (!isPositiveInteger(mokiniuSkInput)) {
            cout << "Netinkama ivestis. Iveskite teigiama sveika skaiciu." << endl;
        }
    } while (!isPositiveInteger(mokiniuSkInput));

    mokiniuSk = stoi(mokiniuSkInput);

    Studentai.resize(mokiniuSk);

    try {
        for (int i = 0; i < mokiniuSk; i++) {
            Studentai[i].Vardas = vardai[rand() % (sizeof(vardai) / sizeof(vardai[0]))];
            Studentai[i].Pavarde = pavardes[rand() % (sizeof(pavardes) / sizeof(pavardes[0]))];
            Studentai[i].n = rand() % 10 + 1;

            for (int j = 1; j <= Studentai[i].n; j++) {
                Studentai[i].nd.push_back(rand() % 10 + 1);
                sum += Studentai[i].nd[j - 1];
            }
            Studentai[i].egz = rand() % 10 + 1;

            // Calculate results for each student individually
            calculateResults(Studentai[i]);
        }
        ChoosePrint();
    } catch (const exception& e) {
        cerr << "Klaida: " << e.what() << endl;
    }
}

void readFromFile() {
    string fileName = "kursiokai.txt";
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cerr << "Unable to open file: " << fileName << endl;
        return;
    }

    while (true) {
        Student student;
        if (!(inputFile >> student.Vardas >> student.Pavarde)) {
            if (inputFile.eof()) {
                break;  // End of file
            } else {
                cerr << "Error reading student information from file." << endl;
                break;
            }
        }

        for (int i = 0; i < 15; ++i) {
            if (!(inputFile >> student.nd[i])) {
                cerr << "Error reading grade " << i + 1 << " for student " << student.Vardas << " " << student.Pavarde << " from file." << endl;
                break;
            }
        }

        if (inputFile.fail()) {
            cerr << "Error reading exam result for student " << student.Vardas << " " << student.Pavarde << " from file." << endl;
            break;
        }

        // Calculate results for each student individually
        calculateResults(student);

        Studentai.push_back(student);
    }

    inputFile.close();
}

int main() {

    int sum = 0;
    int mokiniuSk;
    int choice = 0;

    do {
        cout << "\nMenu:\n";
        cout << "1. Ivesti viska rankomis\n";
        cout << "2. Generuoti pazymius\n";
        cout << "3. Generuoti ir pazymius ir studentu vardus, pavardes\n";
        cout << "4. Gauti studentu vardus, pavardes, pazymius is failo.\n";
        cout << "5. Baigti darba\n";
        cout << "Rinktis (1-5): ";

        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "Neteisinga ivestis. Pasirinkite skaiciu nuo 1 iki 5.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

switch (choice) {
            case 1:
                writeEverythingWithHands();
                break;

            case 2:
                generateRandomGradeInput();
                break;

            case 3:
                generateRandomStudentData(mokiniuSk, sum);
                break;

            case 4:
                readFromFile(); // Add the new option to read data from file
                ChoosePrint();
                break;

            case 5:
                cout << "Programa uzdaroma!\n";
                break;

            default:
                cout << "Neteisingas pasirinkimas. Rinkites nuo 1 iki 5.\n";
        }
    } while (choice != 5);

    return 0;
}
