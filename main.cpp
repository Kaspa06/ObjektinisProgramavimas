#include "studentas.h"
#include "funkcijos.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <stdexcept>
#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    vector<Studentas> studentai;
    int pasirinkimas = 0;

    double visoLaikoSuma = 0.0;
    int testuSkaicius = 0;

    vector<double> testuLaikai;
    vector<int> sizes = {1000, 10000, 100000, 1000000, 10000000};
    vector<Studentas> kietiakiai, vargsiukai;

    while (pasirinkimas != 7) {
        auto startOperation = chrono::high_resolution_clock::now();

        cout << "\nMenu:\n";
        cout << "1. Ivesti viska rankomis\n";
        cout << "2. Generuoti pazymius\n";
        cout << "3. Generuoti ir pazymius ir studentu vardus, pavardes\n";
        cout << "4. Gauti studentu vardus, pavardes, pazymius is failo.\n";
        cout << "5. Generuoti studentu failus.\n";
        cout << "6. Rusiuoti studentus sugeneruotuose failuose.\n";
        cout << "7. Baigti darba\n";
        cout << "Rinktis (1-7): ";

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
                {
                    auto startFileGeneration = std::chrono::high_resolution_clock::now();
                    generateStudentFiles(sizes);
                    auto endFileGeneration = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> elapsedFileGeneration = endFileGeneration - startFileGeneration;
                    std::cout << "Failu generavimas uztruko: " << elapsedFileGeneration.count() << " sekundziu." << std::endl;
                    break;
                }
            case 6:
                {
                    std::cout << "Pasirinkite, kuri studentu faila norite rusiuoti:" << std::endl;
                    for (size_t i = 0; i < sizes.size(); ++i)
                    {
                        std::cout << i + 1 << " - studentai" << sizes[i] << ".txt" << std::endl;
                    }
                    std::cout << "Pasirinkimas: ";
                    size_t choice;
                    std::cin >> choice;

                    if (std::cin.fail() || choice < 1 || choice > sizes.size())
                    {
                        std::cerr << "Neteisingas pasirinkimas." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }

                    auto startSorting = std::chrono::high_resolution_clock::now();
                    rusiuotiStudentus(std::vector<int>{sizes[choice - 1]});
                    auto endSorting = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> elapsedSorting = endSorting - startSorting;
                    std::cout << "Rusiavimas ir issaugojimas uztruko: " << elapsedSorting.count() << " sekundziu." << std::endl;

                    break;
                }
            case 7:
                break;
            default:
                cout << "Neatpazintas pasirinkimas. Bandykite dar karta." << std::endl;
                break;
        }

        if (pasirinkimas != 7) {
            auto endOperation = chrono::high_resolution_clock::now();
            chrono::duration<double> timeOperation = endOperation - startOperation;
            double laikasOperation = timeOperation.count();
            cout << "Operacija uztruko: " << laikasOperation << " s" << endl;
            visoLaikoSuma += laikasOperation;
            testuSkaicius++;
        }
    }

    double vidurkis = visoLaikoSuma / testuSkaicius;
    cout << "Keliu testu laiku vidurkis: " << vidurkis << " s" << endl;

    return 0;
}
