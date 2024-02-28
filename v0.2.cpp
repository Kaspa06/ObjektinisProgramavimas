#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <vector>
#include <limits>
#include <fstream>
#include <cmath>
#include <numeric>
#include <chrono>

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
    return s == "1" || s == "2" || s == "3" || s == "4" || s == "5";
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

void calculateResults(Student& student, int calculationMethod) {
    if (calculationMethod == 1) {
        if (student.n > 0) {
            double sum = accumulate(student.nd.begin(), student.nd.end(), 0.0);
            student.vidurkis = sum / student.n;
        } else {
            student.vidurkis = 0.0;
        }
        student.galutinis = 0.4 * student.vidurkis + 0.6 * student.egz;
    } else {
        sort(student.nd.begin(), student.nd.end());
        student.galutinisMed = (student.n % 2 == 0) ?
            0.4 * (student.nd[student.n / 2 - 1] + student.nd[student.n / 2]) + 0.6 * student.egz :
            0.4 * student.nd[student.n / 2] + 0.6 * student.egz;
    }
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

void ChoosePrint() {
    string choiceInput;
    do {
        cout << "\nKa norite spausdinti: (1 - Galutinis(Vid.), 2 - Galutinis(med.), 5 - Baigti)" << endl;
        cin >> choiceInput;
        if (!isValidChoice(choiceInput)) {
            cout << "Netinkama ivestis. Pasirinkite 1, 2 arba 5." << endl;
        }
    } while (!isValidChoice(choiceInput));

    int choice = stoi(choiceInput);
    if (choice != 5) {
        displayTable(choice);
    }
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
        calculateResults(student, 1);

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

        calculateResults(student, 1);

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
            calculateResults(Studentai[i], 1);
        }
        ChoosePrint();
    } catch (const exception& e) {
        cerr << "Klaida: " << e.what() << endl;
    }
}

double calculateMedian(vector<double>& grades) {
    size_t size = grades.size();
    if (size == 0) {
        return 0.0;
    }

    sort(grades.begin(), grades.end());

    return (size % 2 == 0) ? (grades[size / 2 - 1] + grades[size / 2]) / 2.0 : grades[size / 2];
}

void readDataFromFile() {
    auto start_time = std::chrono::high_resolution_clock::now();
    system("dir *.txt");

    string fileName;
    cout << "Enter the file name to read data from: ";
    cin >> fileName;

    ifstream inputFile(fileName);
    if (!inputFile) {
        cout << "Failed to open the file: " << fileName << endl;
        return;
    }

    vector<Student> tempStudentai;  // Temporary vector for sorting

    while (true) {
        string line;
        if (!(getline(inputFile, line))) {
            break;
        }

        istringstream iss(line);
        Student student;

        if (!(iss >> student.Vardas >> student.Pavarde)) {
            cerr << "Failed to read Vardas and Pavarde." << endl;
            continue;
        }

        double grade;
        student.nd.clear();
        while (iss >> grade) {
            student.nd.push_back(grade);
        }

        if (!student.nd.empty()) {
            student.egz = student.nd.back();
            student.nd.pop_back();
        }

        calculateResults(student, 1);  // Calculate using the average (method 1) by default
        student.galutinisMed = calculateMedian(student.nd);

        tempStudentai.push_back(student);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;
    cout << "Time taken to read data from file: " << elapsed_time.count() << " seconds" << endl;

    int sortCriteria;
    cout << "Select sorting criteria (1 - Vardas, 2 - Pavarde, 3 - Galutinis(Vid.), 4 - Galutinis(Med.)): ";
    cin >> sortCriteria;

    // Sort the data based on the selected criteria
    switch (sortCriteria) {
        case 1:
            sort(tempStudentai.begin(), tempStudentai.end(), [](const Student& a, const Student& b) {
                return a.Vardas < b.Vardas;
            });
            break;
        case 2:
            sort(tempStudentai.begin(), tempStudentai.end(), [](const Student& a, const Student& b) {
                return a.Pavarde < b.Pavarde;
            });
            break;
        case 3:
            sort(tempStudentai.begin(), tempStudentai.end(), [](const Student& a, const Student& b) {
                return a.galutinis < b.galutinis;
            });
            break;
        case 4:
            sort(tempStudentai.begin(), tempStudentai.end(), [](const Student& a, const Student& b) {
                return a.galutinisMed < b.galutinisMed;
            });
            break;
        default:
            cout << "Invalid sorting criteria. Exiting." << endl;
            return;
    }


    cout << "\nSorted data:\n";
    cout << "--------------------------------------------------------------------------------------\n";
    cout << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis(Vid.)" << setw(15) << "Galutinis(Med.)" << endl;
    cout << "--------------------------------------------------------------------------------------\n";

    for (const auto& student : tempStudentai) {
        cout << setw(15) << student.Vardas << setw(15) << student.Pavarde
            << fixed << setprecision(2) << setw(15) << student.galutinis << setw(15) << student.galutinisMed << endl;
    }



        inputFile.close();
        cout << "Data reading and printing successful:)\n";
        tempStudentai.shrink_to_fit();
        cout << "Vector capacity: " << tempStudentai.capacity() << endl;
        cout << "Vector size: " << tempStudentai.size() << endl;
    }

int main() {

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
            generateRandomStudentData(mokiniuSk, 0);
            break;

        case 4:
            readDataFromFile();
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
