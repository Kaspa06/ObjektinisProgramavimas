#include "studentas.h"
#include "funkcijos.h"
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
