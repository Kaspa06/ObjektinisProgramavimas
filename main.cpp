#include "studentas.h"
#include "funkcijos.h"
#include "funkcijosDeque.h"
#include "funkcijosList.h"
#include <iostream>
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
    int pasirinkimas = 0, konteineris = 0, strategija = 0;

    double visoLaikoSuma = 0.0;
    int testuSkaicius = 0;

    vector<double> testuLaikai;
    vector<int> sizes = {1000, 10000, 100000, 1000000, 10000000};
    vector<Studentas> kietiakiai, vargsiukai;

    while (pasirinkimas != 8) {
        auto startOperation = chrono::high_resolution_clock::now();

        cout << "\nMenu:\n";
        cout << "1. Ivesti viska rankomis\n";
        cout << "2. Generuoti pazymius\n";
        cout << "3. Generuoti ir pazymius ir studentu vardus, pavardes\n";
        cout << "4. Gauti studentu vardus, pavardes, pazymius is failo.\n";
        cout << "5. Generuoti studentu failus.\n";
        cout << "6. Rusiuoti studentus sugeneruotuose failuose.\n";
        cout << "7. Rusiuoti studentus pasirenkant konteineri.\n";
        cout << "8. Baigti darba\n";
        cout << "Rinktis (1-8): ";

        cin >> pasirinkimas;
        if (!cin.good()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisinga ivestis. Iveskite skaiciu." << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pasirinkimas) {
            case 1:
                try {
                    manualInput(studentai);
                    PrintData(studentai, "rezultatai.txt");
                } catch (const std::exception &e) {
                    std::cerr << "Ivedimo klaida: " << e.what() << '\n';
                }
                break;
            case 2:
                try {
                    generateGradesOnly(studentai);
                } catch (const std::exception &e) {
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
                    cout << "Neteisinga ivestis. Iveskite skaiciu." << endl;
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
                } catch (const std::exception &e) {
                    std::cerr << "Studentu generavimo klaida: " << e.what() << '\n';
                }
                break;
            case 4: {
                try {
                    readFileDataFromFile(studentai, pasirinktiFaila());
                    int choice = pasirinktiRusiavimoTipa();
                    PrintData(studentai, "rezultatai.txt", choice);
                } catch (const std::exception &e) {
                    std::cerr << e.what() << '\n';
                }
                break;
            }
            case 5: {
                std::cout << "Pasirinkite, kuri studentu faila norite sugeneruoti:" << std::endl;
                for (size_t i = 0; i < sizes.size(); ++i) {
                    std::cout << i + 1 << " - studentai" << sizes[i] << ".txt" << std::endl;
                }
                std::cout << "Pasirinkimas: ";
                size_t choice;
                std::cin >> choice;
                auto startFileGeneration = std::chrono::high_resolution_clock::now();
                generateStudentFiles(std::vector<int>{sizes[choice - 1]});
                auto endFileGeneration = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsedFileGeneration = endFileGeneration - startFileGeneration;
                std::cout << choice << "Failo generavimas uztruko: " << elapsedFileGeneration.count() << " sekundziu." << std::endl;
                break;
            }
            case 6: {
                std::cout << "Pasirinkite, kuri studentu faila norite rusiuoti:" << std::endl;
                for (size_t i = 0; i < sizes.size(); ++i) {
                    std::cout << i + 1 << " - studentai" << sizes[i] << ".txt" << std::endl;
                }
                std::cout << "Pasirinkimas: ";
                size_t choice;
                std::cin >> choice;

                if (std::cin.fail() || choice < 1 || choice > sizes.size()) {
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
            case 7: {
                std::cout << "Pasirinkite, kuri konteineri norite testuoti:" << std::endl;
                std::cout << "1. Vector" << std::endl;
                std::cout << "2. Deque" << std::endl;
                std::cout << "3. List" << std::endl;
                cin >> konteineris;
                std::cout << "Pasirinkite, kuria strategija norite testuoti:" << std::endl;
                std::cout << "1. Du tokio pacio tipo konteineriai" << std::endl;
                std::cout << "2. Vienas konteineris" << std::endl;
                std::cout << "3. Strategija su efektyviais darbo metodais" << std::endl;
                cin >> strategija;

                switch (konteineris) {
                    case 1: {
                        std::cout << "Pradedamas darbas su Vector tipo konteineriais" << endl;
                        if (strategija == 1) {
                            std::cout << "Pasirinkite, kuri studentu faila norite rusiuoti:" << std::endl;
                            for (size_t i = 0; i < sizes.size(); ++i) {
                                std::cout << i + 1 << " - studentai" << sizes[i] << ".txt" << std::endl;
                            }
                            std::cout << "Pasirinkimas: ";
                            size_t choice;
                            std::cin >> choice;

                            if (std::cin.fail() || choice < 1 || choice > sizes.size()) {
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
                        } else if (strategija == 2) {
                            std::cout << "Pasirinkite, kuri studentu faila norite rusiuoti:" << std::endl;
                            for (size_t i = 0; i < sizes.size(); ++i) {
                                std::cout << i + 1 << " - studentai" << sizes[i] << ".txt" << std::endl;
                            }
                            std::cout << "Pasirinkimas: ";
                            size_t choice;
                            std::cin >> choice;

                            if (std::cin.fail() || choice < 1 || choice > sizes.size()) {
                                std::cerr << "Neteisingas pasirinkimas." << std::endl;
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                break;
                            }

                            auto startSorting = std::chrono::high_resolution_clock::now();
                            rusiuotiStudentus2(std::vector<int>{sizes[choice - 1]});
                            auto endSorting = std::chrono::high_resolution_clock::now();
                            std::chrono::duration<double> elapsedSorting = endSorting - startSorting;
                            std::cout << "Rusiavimas ir issaugojimas uztruko: " << elapsedSorting.count() << " sekundziu." << std::endl;
                        } else if (strategija == 3) {
                                                        std::cout << "Pasirinkite, kuri studentu faila norite rusiuoti:" << std::endl;
                            for (size_t i = 0; i < sizes.size(); ++i) {
                                std::cout << i + 1 << " - studentai" << sizes[i] << ".txt" << std::endl;
                            }
                            std::cout << "Pasirinkimas: ";
                            size_t choice;
                            std::cin >> choice;

                            if (std::cin.fail() || choice < 1 || choice > sizes.size()) {
                                std::cerr << "Neteisingas pasirinkimas." << std::endl;
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                break;
                            }

                            auto startSorting = std::chrono::high_resolution_clock::now();
                            rusiuotiStudentus3(std::vector<int>{sizes[choice - 1]});
                            auto endSorting = std::chrono::high_resolution_clock::now();
                            std::chrono::duration<double> elapsedSorting = endSorting - startSorting;
                            std::cout << "Rusiavimas ir issaugojimas uztruko: " << elapsedSorting.count() << " sekundziu." << std::endl;
                        }
                        break;
                    }
                    case 2: {
                        std::cout << "Pradedamas darbas su Deque tipo konteineriais" << endl;
                        break;
                    }
                    case 3: {
                        std::cout << "Pradedamas darbas su List tipo konteineriais" << endl;
                        break;
                    }
                }
                break;
            }
            case 8:
                break;
            default:
                cout << "Neatpazintas pasirinkimas. Bandykite dar karta." << std::endl;
                break;
        }

        if (pasirinkimas != 8) {
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
