#include <iostream>
#include <iomanip>
#include <algorithm> // for std::sort
#include <stdexcept> // for std::invalid_argument

using namespace std;

struct StudentasStruct {
    string Vardas;
    string Pavarde;
    int n;
    int nd[10]; // Adjusted to allow grades between 1 and 10
    double egz;
    double galutinis;
    double galutinisMed;
    double vidurkis;
} Studentai[100]; // Array to store information about up to 100 students

// Funckija tikrinti ar ivestas mok. skaicius yra teigiamas ir ar yra skaicius
bool isPositiveInteger(const string& s) {
    return all_of(s.begin(), s.end(), ::isdigit) && stoi(s) > 0;
}

// Funckija tikrinti ar egzamino rezultatas yra tarp 1.0 ir 10.0
bool isValidDouble(const string& s, double minValue, double maxValue) {
    try {
        double value = stod(s);
        return value >= minValue && value <= maxValue;
    } catch (const invalid_argument&) {
        return false;
    }
}

// tikrinti ar nera klaidu ivesti tarp medianos ir vidurkio pasirinkimo
bool isValidChoice(const string& s) {
    return s == "1" || s == "2";
}

// funkcija tikrinti ar ivesti pazymiai yra tarp 1 ir 10
bool isValidGrade(const string& s) {
    if (all_of(s.begin(), s.end(), ::isdigit)) {
        int grade = stoi(s);
        return grade >= 1 && grade <= 10;
    }
    return false;
}

int main() {
    int sum = 0;
    int mokiniuSk;

    // Input validation for the number of students
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

            // Input validation for the number of grades (pazymiu skaicius)
            string nInput;
            do {
                cout << "Iveskite pazymiu skaiciu: ";
                cin >> nInput;
                if (!isPositiveInteger(nInput)) {
                    cout << "Netinkama ivestis. Iveskite teigiama sveika skaiciu." << endl;
                }
            } while (!isPositiveInteger(nInput));

            Studentai[i].n = stoi(nInput);

            // Input grades
            sum = 0;
            for (int j = 1; j <= Studentai[i].n; j++) {
                string gradeInput;
                do {
                    cout << "Iveskite " << j << " pazymi (nuo 1 iki 10): ";
                    cin >> gradeInput;
                    if (!isValidGrade(gradeInput)) {
                        cout << "Netinkama ivestis. Iveskite skaiciu nuo 1 iki 10." << endl;
                    }
                } while (!isValidGrade(gradeInput));
                Studentai[i].nd[j] = stoi(gradeInput);
                sum += Studentai[i].nd[j];
            }

            Studentai[i].vidurkis = sum / (Studentai[i].n);

            string egzInput; // paiimama ivestis kaip string'as ir tikrinamos salygos >=1 && <=10, ir ar tai yra sk;
            do {
                cout << "Iveskite egzamino rezultata: ";
                cin >> egzInput;
                if (!isValidDouble(egzInput, 1.0, 10.0)) {
                    cout << "Netinkama ivestis. Iveskite skaiciu nuo 1 iki 10." << endl;
                }
            } while (!isValidDouble(egzInput, 1.0, 10.0));

            Studentai[i].egz = stod(egzInput); //string to double

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

    return 0;
}
