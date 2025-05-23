/**
 * @file main.cpp
 * @author Narbas
 * @brief This file handles program's flow 
 * @version v2.0
 * @date 2025-05-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <limits>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "student.h"
#include "functions.h"
#include <iomanip>
#include "utils.h"
#include "vector.h"

double programosLaikas = 0.0;

int main(){

    int pKiekis, meniu;
    float vidurkis, mediana;
    char galutinioBudas, spausBudas, rusiavimoBudas;
    Vector<student> grupe, testGrupe, nepazangus, normalus;
    srand(time(0));
    Vector<std::string>vardai = {"Jonas", "Paulius", "Matas", "Tomas", "Vardenis"};
    Vector<std::string>pavardes = {"Jonavicius", "Pauliavicius", "Matavicius", "Tomavicius", "Pavardenis"};

    while (true) {

        try {
            std::cout << "\nPasirinkite generavimo buda:\n "
                      << "1 - ranka\n "
                      << "2 - generuoti pazymius\n "
                      << "3 - generuoti pazymius studentu vardus, pavardes\n "
                      << "4 - nuskaityti duomenis is failo\n "
                      << "5 - generuoti faila\n "
                      << "6 - generuoto failo nuskaitymas\n "
                      << "7 - ctor ir operatoriu veikimo testai\n"
                      << "8 - std::vector ir nuosavo vector testai\n"
                      << "9 - baigti darba" << std::endl;

            std::cin >> meniu;
            
            if (std::cin.fail()) {
                throw std::runtime_error("Neteisinga ivestis, iveskite skaiciu.");
            }
            if (meniu < 1 || meniu > 9) {
                throw std::runtime_error("Neteisinga ivestis, iveskite skaiciu tarp 1 ir 8.");
            }
            break;
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Klaida: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    if(meniu >=1 && meniu <= 9){

            
        char galutinioBudas = tikrintiInput<char>(
            "Ar norite skaiciuoti galutini ivertinima naudojant pazymiu vidurki ar mediana (v/m)? ", 
            "Klaidingai ivestas balo budas.\n"
        );

        while (galutinioBudas != 'v' && galutinioBudas != 'm') {
            std::cerr << "Klaida: Netinkamas pasirinkimas. Bandykite dar karta." << std::endl;
            galutinioBudas = tikrintiInput<char>(
                "Ar norite skaiciuoti galutini ivertinima naudojant pazymiu vidurki ar mediana (v/m)? ", 
                "Klaidingai ivestas balo budas.\n"
            );
        }

        char spausBudas = tikrintiInput<char>(
            "Ar norite duomenis matyti terminale ar faile? (t/f) ", 
            "Klaidingai ivestas spausdinimo budas.\n"
        );

        while (spausBudas != 't' && spausBudas != 'f') {
            std::cerr << "Klaida: Netinkamas pasirinkimas. Bandykite dar karta." << std::endl;
            spausBudas = tikrintiInput<char>(
                "Ar norite duomenis matyti terminale ar faile? (t/f) ", 
                "Klaidingai ivestas spausdinimo budas.\n"
            );
        }

        char rusiavimoBudas = tikrintiInput<char>(
            "Ar noresite studentus rusiuoti pagal pavarde ar pagal galutini pazymi? (p/g) ", 
            "Klaidingai ivestas rusiavimo budas.\n"
        );

        while (rusiavimoBudas != 'p' && rusiavimoBudas != 'g') {
            std::cerr << "Klaida: Netinkamas pasirinkimas. Bandykite dar karta." << std::endl;
            rusiavimoBudas = tikrintiInput<char>(
                "Ar noresite studentus rusiuoti pagal pavarde ar pagal galutini pazymi? (p/g) ", 
                "Klaidingai ivestas rusiavimo budas.\n"
            );
        }

        int pKiekis = tikrintiInput<int>(
            "Iveskite pazymiu kieki: ", 
            "Blogai ivestas pazymiu kiekis.\n"
        );
        
    bool ciklas = true;
    while(ciklas){
        switch (meniu)
        {
        case 1:
            pirmas(grupe, spausBudas, rusiavimoBudas, galutinioBudas, pKiekis);
            break;

        case 2:
            antras(grupe, spausBudas, rusiavimoBudas, galutinioBudas, pKiekis);
            break;
        
        case 3:
            trecias(grupe, vardai, pavardes,  spausBudas, rusiavimoBudas, galutinioBudas, pKiekis);
            break;

        case 4:
            ketvirtas(grupe, pKiekis, galutinioBudas);
            break;

        case 5:
            penktas(pKiekis);
            break;

        case 6:
            sestas(grupe, testGrupe, nepazangus, normalus, galutinioBudas, rusiavimoBudas, pKiekis);
            break;

        case 7:
            septintas(galutinioBudas);
            break;
        case 8:
            astuntas();
            break;
        case 9:
            std::cout << "Isejote is programos." << std::endl;
            ciklas = false;
            break;
        default:
            std::cout << "Ivedete bloga skaiciu, veskite is naujo: \n";
            continue;
        }

        std::cout << "Pasirinkite kita veiksma (1-9): " << std::endl;
        std::cin >> meniu;

        while(meniu < 1 || meniu > 9){
            std::cout << "Ivedete neteisinga skaiciu, veskite is naujo: " << std::endl;
            std::cin >> meniu;
        }
    }

    return 0;
}}
