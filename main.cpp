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
        if (!cin.good()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch (pasirinkimas) {
            case 1:
                try {
                    manualInput(studentai);
                    PrintData(studentai, "rezultatai.txt");
                } catch (const std::exception& e) {
                    std::cerr << "Ivedimo klaida: " << e.what() << '\n';
                }
                break;
            case 2:
                 try {
                    generateGradesOnly(studentai);
                } catch (const std::exception& e) {
                    std::cerr << "Pazymiu generavimo klaida: " << e.what() << '\n';
                }
                break;
            case 3:
                int laik;
                cout << "Iveskite kieki, kiek norite sugeneruoti studentu:";
                cin >> laik;
                if (!cin.good()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number." << endl;
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer

                try {     
                    for (int i = 0; i < laik; ++i) {
                        Studentas naujasStudentas;
                        generateRandomNamesAndGrades(naujasStudentas);
                        studentai.push_back(naujasStudentas);
                        PrintData(studentai, "rezultatai.txt", 1);
                    }
                }
                catch (const std::exception& e) {
                    std::cerr << "Studentu generavimo klaida: " << e.what() << '\n';
                }
                break;
            case 4:
                {
                    try{               
                        readFileDataFromFile(studentai, pasirinktiFaila());
                        int choice = pasirinktiRusiavimoTipa();
                        PrintData(studentai, "rezultatai.txt", choice);
                    }
                    catch(const std::exception& e){
                        std::cerr << e.what() << '\n';
                    }
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
