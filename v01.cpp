#include <iostream>
#include <iomanip>

using namespace std;

struct StudentasStruct {
    string Vardas;
    string Pavarde;
    int n;
    int nd[100];
    double egz;
    double galutinis;
    double vidurkis;
} Studentas;

int main() {
    int sum = 0;
    cout << "Iveskite Varda: ";
    cin >> Studentas.Vardas;
    cout << "Iveskite Pavarde: ";
    cin >> Studentas.Pavarde;
    cout << "Iveskite pazymiu skaiciu: ";
    cin >> Studentas.n;

    for (int i = 1; i <= Studentas.n; i++) {
        cout << "Iveskite " << i << " pazymi: ";
        cin >> Studentas.nd[i];
        sum = sum + Studentas.nd[i];
    }

    Studentas.vidurkis = sum / Studentas.n;

    cout << "Iveskite egzamino rezultata: ";
    cin >> Studentas.egz;

    Studentas.galutinis = 0.4 * Studentas.vidurkis + 0.6 * Studentas.egz;

    // Beautiful cout with Vardas, Pavarde, Galutinis, and fixed positions
    cout << "\nInformacija apie studenta:\n";
    cout << "---------------------------------\n";
    cout << setw(10) << "Vardas" << setw(10) << "Pavarde" << setw(10) << "Galutinis" << endl;
    cout << "---------------------------------\n";
    cout << setw(10) << Studentas.Vardas << setw(10) << Studentas.Pavarde << setw(7) << Studentas.galutinis << endl;

    return 0;
}
