#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <ctime> // for generating random values

using namespace std;

string vardai[] = {"Jonas", "Petras", "Ona", "Maryte", "Antanas", "Jurga", "Kazys", "Rasa", "Darius", "Aiste"};
string pavardes[] = {"Jonaitis", "Petraitis", "Onute", "Marytiene", "Antanaitis", "Jurgaite", "Kaziukas", "Rasiene", "Dariukas", "Aistyte"};

struct StudentasStruct {
    string Vardas;
    string Pavarde;
    int n;
    int nd[10];
    double egz;
    double galutinis;
    double galutinisMed;
    double vidurkis;
} Studentai[100];

bool isPositiveInteger(const string& s) {
    return all_of(s.begin(), s.end(), ::isdigit) && stoi(s) > 0;
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

void writeEverythingWithHands() {
    int mokiniuSk;
    string mokiniuSkInput;
    do {
        cout << "Iveskite kiek bus mokiniu: ";
        cin >> mokiniuSkInput;
        if (!isPositiveInteger(mokiniuSkInput)) {
            cout << "Netinkama ivestis. Iveskite teigiama sveika skaiciu." << endl;
        }
    } while (!isPositiveInteger(mokiniuSkInput));

    mokiniuSk = stoi(mokiniuSkInput);

    try {
        // Input information for each student
        for (int i = 0; i < mokiniuSk; i++) {
            cout << "Iveskite Varda: ";
            cin >> Studentai[i].Vardas;
            cout << "Iveskite Pavarde: ";
            cin >> Studentai[i].Pavarde;

            // Input grades
            double sum = 0;
            int j = 0;
            do {
                cout << "Iveskite " << j + 1 << " pazymi (nuo 1 iki 10, arba -1 jei norite baigti): ";
                string gradeInput;
                cin >> gradeInput;

                if (gradeInput == "-1") {
                    break; // Exit the loop if user inputs -1
                }

                if (!isValidGrade(gradeInput)) {
                    cout << "Netinkama ivestis. Iveskite skaiciu nuo 1 iki 10." << endl;
                } else {
                    Studentai[i].nd[j] = stod(gradeInput);
                    sum += Studentai[i].nd[j];
                    j++;
                }
            } while (true);

            Studentai[i].n = j; // Number of grades entered

            // Input exam result
            string egzInput;
            do {
                cout << "Iveskite egzamino rezultata: ";
                cin >> egzInput;
                if (!isValidDouble(egzInput, 1.0, 10.0)) {
                    cout << "Netinkama ivestis. Iveskite skaiciu nuo 1 iki 10." << endl;
                }
            } while (!isValidDouble(egzInput, 1.0, 10.0));

            Studentai[i].egz = stod(egzInput);

            // Calculate final results
            Studentai[i].vidurkis = sum / Studentai[i].n;
            Studentai[i].galutinis = 0.4 * Studentai[i].vidurkis + 0.6 * Studentai[i].egz;

            // Assuming nd array is sorted, calculate median
            int n = Studentai[i].n;
            Studentai[i].galutinisMed = (n % 2 == 0) ?
                                        0.4 * (Studentai[i].nd[n / 2 - 1] + Studentai[i].nd[n / 2]) + 0.6 * Studentai[i].egz :
                                        0.4 * Studentai[i].nd[n / 2] + 0.6 * Studentai[i].egz;
        }

        // Choose between average and median
        string choiceInput;
        do {
            cout << "\nKa norite spausdinti: (1 - Galutinis(Vid.), 2 - Galutinis(med.))" << endl;
            cin >> choiceInput;
            if (!isValidChoice(choiceInput)) {
                cout << "Netinkama įvestis. Pasirinkite 1 arba 2." << endl;
            }
        } while (!isValidChoice(choiceInput));

        int choice = stoi(choiceInput);

        // Display the table
        cout << "\nInformacija apie studentus:\n";
        cout << "--------------------------------------------------------------------------------------\n";
        cout << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << (choice == 1 ? "Galutinis(Vid.)" : "Galutinis(med.)") << endl;
        cout << "--------------------------------------------------------------------------------------\n";

        for (int i = 0; i < mokiniuSk; i++) {
            cout << setw(15) << Studentai[i].Vardas << setw(15) << Studentai[i].Pavarde
            << fixed << setprecision(2) << setw(20) << (choice == 1 ? Studentai[i].galutinis : Studentai[i].galutinisMed) << endl;

        }
    } catch (const exception& e) {
        cerr << "Klaida: " << e.what() << endl;
    }
}

void generateRandomGradeInput(int mokiniuSk, int sum) {
    string mokiniuSkInput;
    do {
        cout << "Iveskite kiek bus mokiniu: ";
        cin >> mokiniuSkInput;
        if (!isPositiveInteger(mokiniuSkInput)) {
            cout << "Netinkama ivestis. Iveskite teigiama sveika skaiciu." << endl;
        }
    } while (!isPositiveInteger(mokiniuSkInput));

    mokiniuSk = stoi(mokiniuSkInput);

    try {
        // Input information for each student
        for (int i = 0; i < mokiniuSk; i++) {
            cout << "Iveskite Varda: ";
            cin >> Studentai[i].Vardas;
            cout << "Iveskite Pavarde: ";
            cin >> Studentai[i].Pavarde;

            Studentai[i].n = rand() % 10 + 1; // nd KIEKIS nuo 1 iki 10

            for (int j = 0; j < Studentai[i].n; j++) {
                Studentai[i].nd[j] = rand() % 10 + 1; // nd balai nuo 1 iki 10
                sum += Studentai[i].nd[j];
            }

            Studentai[i].vidurkis = sum / static_cast<double>(Studentai[i].n);

            Studentai[i].egz = rand() % 10 + 1; // egzo balas nuo 1 iki 10 

            Studentai[i].galutinis = 0.4 * Studentai[i].vidurkis + 0.6 * Studentai[i].egz;
            Studentai[i].galutinisMed = 0.4 * ((Studentai[i].nd[Studentai[i].n / 2] + Studentai[i].nd[(Studentai[i].n - 1) / 2]) / 2.0) + 0.6 * Studentai[i].egz;
        }

        // Pasirinkimas tarp vidurkio ir medianos
        string choiceInput;
        do {
            cout << "\nKa norite spausdinti: (1 - Galutinis(Vid.), 2 - Galutinis(med.))" << endl;
            cin >> choiceInput;
            if (!isValidChoice(choiceInput)) {
                cout << "Netinkama įvestis. Pasirinkite 1 arba 2." << endl;
            }
        } while (!isValidChoice(choiceInput));

        int choice = stoi(choiceInput);

        // Lenteles isvedimas
        cout << "\nInformacija apie studentus:\n";
        cout << "--------------------------------------------------------------------------------------\n";
        cout << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << (choice == 1 ? "Galutinis(Vid.)" : "Galutinis(med.)") << endl;
        cout << "--------------------------------------------------------------------------------------\n";

        for (int i = 0; i < mokiniuSk; i++) {
            cout << setw(15) << Studentai[i].Vardas << setw(15) << Studentai[i].Pavarde
                << setw(20) << (choice == 1 ? Studentai[i].galutinis : Studentai[i].galutinisMed) << endl;
        }
    } catch (const exception& e) {
        cerr << "Klaida: " << e.what() << endl;
    };
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

    try {
        // Input information for each student
        for (int i = 0; i < mokiniuSk; i++) {
            // Generate random Vardas
            Studentai[i].Vardas = vardai[rand() % (sizeof(vardai) / sizeof(vardai[0]))];

            // Generate random Pavarde
            Studentai[i].Pavarde = pavardes[rand() % (sizeof(pavardes) / sizeof(pavardes[0]))];

            // Generate random pazymiu skaicius (n)
            Studentai[i].n = rand() % 10 + 1;

            // Generate random pazymiai (nd)
            sum = 0;
            for (int j = 1; j <= Studentai[i].n; j++) {
                Studentai[i].nd[j] = rand() % 10 + 1;
                sum += Studentai[i].nd[j];
            }

            // Calculate vidurkis
            Studentai[i].vidurkis = sum / static_cast<double>(Studentai[i].n);

            // Generate random egzamino rezultatas
            Studentai[i].egz = rand() % 10 + 1;

            // Calculate galutinis and galutinisMed
            Studentai[i].galutinis = 0.4 * Studentai[i].vidurkis + 0.6 * Studentai[i].egz;
            Studentai[i].galutinisMed = 0.4 * ((Studentai[i].nd[Studentai[i].n / 2] + Studentai[i].nd[(Studentai[i].n - 1) / 2]) / 2.0) + 0.6 * Studentai[i].egz;
        }

        // Pasirinkimas tarp vidurkio ir medianos
        string choiceInput;
        do {
            cout << "\nKa norite spausdinti: (1 - Galutinis(Vid.), 2 - Galutinis(med.))" << endl;
            cin >> choiceInput;
            if (!isValidChoice(choiceInput)) {
                cout << "Netinkama įvestis. Pasirinkite 1 arba 2." << endl;
            }
        } while (!isValidChoice(choiceInput));

        int choice = stoi(choiceInput);

        // Lenteles isvedimas
        cout << "\nInformacija apie studentus:\n";
        cout << "--------------------------------------------------------------------------------------\n";
        cout << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << (choice == 1 ? "Galutinis(Vid.)" : "Galutinis(med.)") << endl;
        cout << "--------------------------------------------------------------------------------------\n";

        for (int i = 0; i < mokiniuSk; i++) {
            cout << setw(15) << Studentai[i].Vardas << setw(15) << Studentai[i].Pavarde
                << setw(20) << (choice == 1 ? Studentai[i].galutinis : Studentai[i].galutinisMed) << endl;
        }
    } catch (const exception& e) {
        cerr << "Klaida: " << e.what() << endl;
    }
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
        cout << "4. baigti darba\n";
        cout << "Rinktis (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                writeEverythingWithHands();
                break;

            case 2:
                generateRandomGradeInput(mokiniuSk, sum);
                break;

            case 3:
                generateRandomStudentData(mokiniuSk, sum);
                break;

            case 4:
                cout << "Programa uzdaroma!\n";
                break;

            default:
                cout << "Neteisingas pasirinkimas. Rinkites nuo 1 iki 4.\n";
        }
    } while (choice != 4);

    return 0;
}
