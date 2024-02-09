#include <iostream>
#include <iomanip>
#include <algorithm> // for std::sort

using namespace std;

struct StudentasStruct {
    string Vardas;
    string Pavarde;
    int n;
    int nd[100];
    double egz;
    double galutinis;
    double galutinisMed;
    double vidurkis;
} Studentai[100]; // Array to store information about up to 100 students

int main() {
    int sum = 0;
    int mokiniuSk;
    cout << "Iveskite kiek mus mokiniu:" << endl;
    cin >> mokiniuSk;

    // Input information for each student
    for (int i = 0; i < mokiniuSk; i++) {
        cout << "Iveskite Varda: ";
        cin >> Studentai[i].Vardas;
        cout << "Iveskite Pavarde: ";
        cin >> Studentai[i].Pavarde;
        cout << "Iveskite pazymiu skaiciu: ";
        cin >> Studentai[i].n;

        sum = 0;
        for (int j = 1; j <= Studentai[i].n; j++) {
            cout << "Iveskite " << j << " pazymi: ";
            cin >> Studentai[i].nd[j];
            sum = sum + Studentai[i].nd[j];
        }

        Studentai[i].vidurkis = sum / Studentai[i].n;

        // Calculate galutinis using the old formula
        cout << "Iveskite egzamino rezultata: ";
        cin >> Studentai[i].egz;
        Studentai[i].galutinis = 0.4 * Studentai[i].vidurkis + 0.6 * Studentai[i].egz;

        // Calculate galutinisMed using the new formula
        Studentai[i].galutinisMed = 0.4 * ((Studentai[i].nd[Studentai[i].n / 2] + Studentai[i].nd[(Studentai[i].n - 1) / 2]) / 2.0) + 0.6 * Studentai[i].egz;
    }

    // Beautiful cout with Vardas, Pavarde, Galutinis, and Galutinis(med.) for all students
    cout << "\nInformacija apie studentus:\n";
    cout << "--------------------------------------------------------------------------------------\n";
    cout << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis(Vid.)" << setw(20) << "Galutinis(med.)" << endl;
    cout << "--------------------------------------------------------------------------------------\n";

    for (int i = 0; i < mokiniuSk; i++) {
        cout << setw(15) << Studentai[i].Vardas << setw(15) << Studentai[i].Pavarde
             << setw(15) << Studentai[i].galutinis << setw(20) << Studentai[i].galutinisMed << endl;
    }

    return 0;
}
