/**
 * @file functions.cpp
 * @author Narbas
 * @brief this file contains all functions
 * @version v2.0
 * @date 2025-05-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "functions.h"
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <chrono>
#include <sstream>
#include <random>
#include "student.h"
#include "functions.h"
#include "vector.h"

extern double programosLaikas;

void rusiuotiOutput(std::vector<student>& grupe, char rusiavimoBudas, char galutinioBudas){
    
    if(rusiavimoBudas == 'p'){
        std::sort(grupe.begin(), grupe.end(), [](const student& a, const student& b){
            if(a.getPavarde() == b.getPavarde()){
                return a.getVardas() < b.getVardas();
            }
            return a.getPavarde() < b.getPavarde();
        });
    }
    else{
        std::sort(grupe.begin(), grupe.end(), [galutinioBudas](const student& a, const student& b){
            if(galutinioBudas == 'v'){
                return a.getGalutinisV() > b.getGalutinisV();
            }
            else{
                return a.getGalutinisM() > b.getGalutinisM();
            }
        });
    }
}

void spausdinimasTerminale(const std::vector<student>& grupe, char galutinioBudas){

    std::cout << std::left << std::setw(15) << "Pavarde" << std::setw(20) << "Vardas" << std::setw(20) << "Galutinis(vid./med.)" << '\n'
      << "-------------------------------------------------------------------" << '\n';

    std::cout << std::fixed << std::setprecision(2) << std::left;

    if (galutinioBudas == 'v') {
        for (auto const &s : grupe) {
            std::cout
              << std::setw(15) << s.getPavarde()
              << std::setw(17) << s.getVardas()
              << std::setw(20) << s.getGalutinisV()
              << '\n';
        }
    }
    else {
        for (auto const &s : grupe) {
            std::cout
              << std::setw(15) << s.getPavarde()
              << std::setw(17) << s.getVardas()
              << std::setw(20) << s.getGalutinisM()
              << '\n';
        }
    }
}

void spausdinimasFaile(const std::vector<student>& grupe, char galutinioBudas){

    std::ofstream outFile("duomenys.txt");
    if (!outFile) {
        std::cerr << "Nepavyko atidaryti failo: " << '\n';
        return;
    }

    outFile 
      << std::left << std::setw(15) << "Pavarde"
      << std::setw(20) << "Vardas"
      << std::setw(20) << "Galutinis(vid./med.)" << '\n'
      << "-------------------------------------------------------------------" << '\n';

    outFile << std::fixed << std::setprecision(2) << std::left;

    if (galutinioBudas == 'v') {
        for (auto const &s : grupe) {
            outFile
              << std::setw(15) << s.getPavarde()
              << std::setw(17) << s.getVardas()
              << std::setw(30) << s.getGalutinisV()
              << '\n';
        }
    }
    else {
        for (auto const &s : grupe) {
            outFile
              << std::setw(15) << s.getPavarde()
              << std::setw(17) << s.getVardas()
              << std::setw(30) << s.getGalutinisM()
              << '\n';
        }
    }
}

void generuotiFaila(int pKiekis, int studentuKiekis, const std::string& failoPavadinimas){

    std::ofstream outFile(failoPavadinimas);

    if (!outFile) {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << '\n';
        return;
    }

    outFile << std::left;
    outFile << std::setw(15) << "Pavarde" << std::setw(30) << "Vardas";

    for (int j = 1; j <= pKiekis; ++j) {
        outFile << std::setw(8) << ("ND" + std::to_string(j));
    }

    outFile << std::setw(10) << "Egzaminas" << '\n';
    outFile << std::string(15 + 30 + pKiekis*8 + 10, '-') << '\n';

    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(1, 10);

    for (int i = 1; i <= studentuKiekis; ++i) {
        outFile << std::setw(15) << ("Pavarde" + std::to_string(i)) << std::setw(30) << ("Vardas"  + std::to_string(i));
        for (int j = 0; j < pKiekis; ++j){
            outFile << std::setw(8) << dist(rng);
        }
        outFile << std::setw(10) << dist(rng) << '\n';
    }
}

void spausdinimas(char spausBudas, char rusiavimoBudas, char galutinioBudas, std::vector<student>& grupe){

    while (spausBudas != 't' && spausBudas != 'f') {
        std::cout << "Pasirinkite t/f: ";
        std::cin  >> spausBudas;
    }

    rusiuotiOutput(grupe, rusiavimoBudas, galutinioBudas);

    if (spausBudas == 't') {
        spausdinimasTerminale(grupe, galutinioBudas);
    }
    else{
        spausdinimasFaile(grupe, galutinioBudas);
    }
}

void sortedStudentSpausdinimas(std:: string lowGradeFailas, std::string highGradeFailas, std::vector<student>&nepazangus, std::vector<student>&normalus, char galutinioBudas){
    std::ofstream outFile(lowGradeFailas);

    if (!outFile.is_open()) {
        std::cout << "Nepavyko atidaryti failo." << std::endl;
        return;
    }

    auto spausdinimoPradzia = std::chrono::high_resolution_clock::now();

    outFile << std::left << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas" << std::setw(25) << "Galutinis(vid./med.)" << std::endl;
        outFile << "-----------------------------------------------------------------------------------------------------------------" << std::endl;


    if(galutinioBudas == 'v'){
        for(const auto& studentas : nepazangus){
            
            outFile << std::left << std::setw(15) << studentas.getPavarde() << std::setw(15) << studentas.getVardas() << std::setw(25)
            << std::setprecision(2) << studentas.getGalutinisV() << std::endl;
        }
    }
    else{
        for(const auto& studentas : nepazangus){
            
            outFile << std::left << std::setw(15) << studentas.getPavarde() << std::setw(15) << studentas.getVardas() << std::setw(25)
            << std::setprecision(2) << studentas.getGalutinisM() << std::endl;
        }
    }

    auto spausdinimoPabaiga = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> spausdinimoLaikas = spausdinimoPabaiga - spausdinimoPradzia;
    std::cout  <<"Nepazangiu studentu spausdinimas i faila uztruko: " << std::fixed << std::setprecision(4) << spausdinimoLaikas.count() << "s" << std::endl;

    programosLaikas += spausdinimoLaikas.count();

    outFile.close();

    std::ofstream outFile1(highGradeFailas);

    if (!outFile1.is_open()) {
        std::cout << "Nepavyko atidaryti failo." << std::endl;
        return;
    }

    auto spausdinimoPradzia1 = std::chrono::high_resolution_clock::now();

    outFile1 << std::left << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas" << std::setw(25) << "Galutinis(vid./med.)" << std::endl;
        outFile1 << "-----------------------------------------------------------------------------------------------------------------" << std::endl;


    if(galutinioBudas == 'v'){
        for(const auto& studentas : normalus){
            
            outFile1 << std::left << std::setw(15) << studentas.getPavarde() << std::setw(15) << studentas.getVardas() << std::setw(25)
            << std::setprecision(2) << studentas.getGalutinisV() << std::endl;
        }
    }       
    else{
        for(const auto& studentas : normalus){
            
            outFile1 << std::left << std::setw(15) << studentas.getPavarde() << std::setw(15) << studentas.getVardas() << std::setw(25)
            << std::setprecision(2) << studentas.getGalutinisM() << std::endl;
        }
    } 
    
    outFile1.close();
    
    auto spausdinimoPabaiga1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> spausdinimoLaikas1 = spausdinimoPabaiga1 - spausdinimoPradzia1;
    std::cout  <<"Normaliu studentu spausdinimas i faila uztruko: " << std::fixed << std::setprecision(4) << spausdinimoLaikas1.count() << "s" << std::endl;
    programosLaikas += spausdinimoLaikas1.count();
}

void nuskaitytiGeneruotusFailus(const std::string& failoPavadinimas, std::vector<student>& grupe, int pKiekis, char galutinioBudas){

    std::ifstream inFile(failoPavadinimas);
    if (!inFile) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);
    }

    std::string l;
    std::getline(inFile, l);
    std::getline(inFile, l);

    std::vector<float> pazymiai;
    pazymiai.reserve(pKiekis);

    std::string vardas, pavarde;
    float egzaminas;

    while (inFile >> vardas >> pavarde) {
        pazymiai.clear();

        for (int i = 0; i < pKiekis; ++i) {
            float val;
            inFile >> val;
            pazymiai.push_back(val);
        }

        inFile >> egzaminas;

        grupe.emplace_back(std::move(vardas), std::move(pavarde), std::move(pazymiai), std::move(egzaminas));
        grupe.back().skaiciuotiGalutini(galutinioBudas);
    }
}
void skirstytiStudentus(std::vector<student>& grupe, std::vector<student>& nepazangus, std::vector<student>& normalus, char galutinioBudas){

    size_t n = grupe.size();
    normalus.clear();   normalus.reserve(n);
    nepazangus.clear(); nepazangus.reserve(n);

    if (galutinioBudas == 'v') {
        for (auto& s : grupe) {
            if (s.getGalutinisV() > 5.0f){
                normalus.push_back(std::move(s));
            }
            else{
                nepazangus.push_back(std::move(s));
            }    
        }
    } 
    else {
        for (auto& s : grupe) {
            if (s.getGalutinisM() > 5.0f){
                normalus.push_back(std::move(s));
            }
            else{
                nepazangus.push_back(std::move(s));
            }
        }
    }
    grupe.clear();
}
void pirmas(std::vector<student>& grupe, char spausBudas, char rusiavimoBudas, char galutinioBudas, int pKiekis){
    
    std::string tempVardas, tempPavarde;
    std::vector<float> pazymiai;
    float tempEgz = 0.0f;
    pazymiai.reserve(pKiekis);

    while(true){
        try{
            std::cout << "Iveskite studento varda: " << std::endl;
            std::cin >> tempVardas;
            if(std::cin.fail()){
                throw std::runtime_error("klaidingai ivestas vardas.");
            }
            std::cout << std::endl;
            break;
        }
        catch(const std::runtime_error& e){
            std::cerr << "Klaida: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    while(true){
        try{
            std::cout << "Iveskite studento pavarde: " << std::endl;
            std::cin >> tempPavarde;
            if(std::cin.fail()){
                throw std::runtime_error("klaidingai ivesta pavarde");
            }
            std::cout << std::endl;
            break;
        }
        catch(const std::runtime_error& e){
            std::cerr << "Klaida: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    while(true){
        try{
            std::cout << "Iveskite pazymius: " << std::endl;
            pazymiai.clear();

            for(int i = 0; i < pKiekis; i++){
                int pazymys = 0;
                std::cout << "Pazymys " << i + 1 << ". ";
                std::cin >> pazymys;
                if(std::cin.fail()){
                    throw std::runtime_error("klaidingai ivestas pazymiu skaicius");
                }
                pazymiai.push_back(pazymys);
            }
            std::cout << std::endl;
            break;
        }
        catch(const std::runtime_error& e){
            std::cerr << "Klaida: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    while(true){
        try{
            std::cout << "Iveskite egzamino pazymi: " << std::endl;
            std::cin >> tempEgz;
            
            if(std::cin.fail()){
                throw std::runtime_error("klaidingai ivestas egzamino pazymys.");
            }
            std::cout << std::endl;
            break;
        }
        catch(const std::runtime_error& e){
            std::cerr << "Klaida: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    }
    
    grupe.emplace_back(std::move(tempVardas), std::move(tempPavarde), std::move(pazymiai), std::move(tempEgz));
    grupe.back().skaiciuotiGalutini(galutinioBudas);
    spausdinimas(spausBudas, rusiavimoBudas, galutinioBudas, grupe);
    
}
void antras(std::vector<student>& grupe, char spausBudas, char rusiavimoBudas, char galutinioBudas, int pKiekis){

    std::string tempVardas, tempPavarde;
    std::vector<float> pazymiai;
    pazymiai.reserve(pKiekis);

    std::cout << "Iveskite studento varda: " << std::endl;
    std::cin >> tempVardas;
    std::cout << "Iveskite studento pavarde: " << std::endl;
    std::cin >> tempPavarde;

    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(1,10);

    for (int i = 0; i < pKiekis; ++i) {
        pazymiai.push_back(dist(rng));
    }

    float tempEgz = dist(rng);

    grupe.emplace_back(std::move(tempVardas), std::move(tempPavarde), std::move(pazymiai), std::move(tempEgz));
    grupe.back().skaiciuotiGalutini(galutinioBudas);
    spausdinimas(spausBudas, rusiavimoBudas, galutinioBudas, grupe);
}
void trecias(std::vector<student>& grupe, const std::vector<std::string>& vardai, const std::vector<std::string>& pavardes, char spausBudas, char rusiavimoBudas, char galutinioBudas, int pKiekis){

    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> xDist(0, vardai.size()-1);
    std::uniform_int_distribution<int> gradeDist(1,10);

    int x = xDist(rng);

    std::vector<float> pazymiai;
    pazymiai.reserve(pKiekis);
    for (int i = 0; i < pKiekis; ++i) {
        pazymiai.push_back(gradeDist(rng));
    }
    float egzaminas = gradeDist(rng);

    grupe.emplace_back(std::move(vardai[x]), std::move(pavardes[x]), std::move(pazymiai), std::move(egzaminas));
    grupe.back().skaiciuotiGalutini(galutinioBudas);
    spausdinimas(spausBudas, rusiavimoBudas, galutinioBudas, grupe);
}

void ketvirtas(std::vector<student>& grupe, int pKiekis, char galutinioBudas) {
    auto pradzia = std::chrono::steady_clock::now();

    std::ifstream inFile("studentai10000.txt");
    if (!inFile.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti failo.");
    }

    std::string topLine;
    std::getline(inFile, topLine);

    while (true) {
        std::string line;
        if (!std::getline(inFile, line))
            break;
        if (line.empty())
            continue;


        std::vector<float> pazymiai;
        pazymiai.reserve(pKiekis);
        std::istringstream token(line);
        std::string tempVardas, tempPavarde;
        float tempEgz;
        while (inFile >> tempVardas >> tempPavarde) {
            pazymiai.clear();
            for (int i = 0; i < pKiekis; ++i) {
                float v;
                inFile >> v;
                pazymiai.push_back(v);
            }
            inFile >> tempEgz;

            grupe.emplace_back(std::move(tempVardas), std::move(tempPavarde), std::move(pazymiai), std::move(tempEgz));
            grupe.back().skaiciuotiGalutini(galutinioBudas);
        }

        auto pabaiga = std::chrono::steady_clock::now();
        std::chrono::duration<double> trukme = pabaiga - pradzia;
        std::cout << "Uztruko " << trukme.count() << " sekundziu." << std::endl;
    }
}

void penktas(int pKiekis){

    for(int i = 0; i < 5; i++){
        std::string failoPavadinimas = "test.txt";
        failoPavadinimas.insert(4, 1, '0' + (i+1));
        std::cout << "Iveskite studentu kieki " << (i+1) << ". failui: " << std::endl;
        int studentuKiekis;
        std::cin >> studentuKiekis;

        auto generavimoPradzia = std::chrono::high_resolution_clock::now();
        generuotiFaila(pKiekis, studentuKiekis, failoPavadinimas);
        auto generavimoPabaiga = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> generavimoLaikas = generavimoPabaiga - generavimoPradzia;
        std::cout << failoPavadinimas <<" generavimo laikas: " << std::fixed << std::setprecision(4) << generavimoLaikas.count() << "s" << std::endl;
        programosLaikas += generavimoLaikas.count();
    }
}
void sestas(std::vector<student>& grupe, std::vector<student>& testGrupe, std::vector<student>& nepazangus, std::vector<student>& normalus, char galutinioBudas, char rusiavimoBudas, int pKiekis){
    student studentas;
    testGrupe.clear();
    normalus.clear();
    nepazangus.clear();
    programosLaikas = 0.0;
    
    for (int i = 1; i <= 5; ++i) {
        std::string failoClearinimas = "nepazangus" + std::to_string(i) + ".txt";
        std::ofstream ofs(failoClearinimas, std::ios::trunc);
    }
    for (int i = 1; i <= 5; ++i) {
        std::string failoClearinimas1 = "normalus" + std::to_string(i) + ".txt";
        std::ofstream ofs(failoClearinimas1, std::ios::trunc);
    }

    for(int i = 0; i < 5; i++){
        
        std::string failoPavadinimas = "test.txt";
        failoPavadinimas.insert(4, 1, '0' + (i+1));

        std::string lowGradeFailas = "nepazangus.txt";
        lowGradeFailas.insert(10, 1, '0' + (i+1));

        std::string highGradeFailas = "normalus.txt";
        highGradeFailas.insert(8, 1, '0' + (i+1));

        std::cout << "-----------------------------------------------------------" << std::endl;
        std::cout << failoPavadinimas << std::endl;
        std::cout << std::endl;

        auto nuskaitymoPradzia = std::chrono::high_resolution_clock::now();
        nuskaitytiGeneruotusFailus(failoPavadinimas, testGrupe, pKiekis, galutinioBudas);
        auto nuskaitymoPabaiga = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> nuskaitymoLaikas = nuskaitymoPabaiga - nuskaitymoPradzia;
        std::cout << failoPavadinimas <<": failo nuskaitymas uztruko  " << std::fixed << std::setprecision(4) << nuskaitymoLaikas.count() << "s" << std::endl;
        programosLaikas += nuskaitymoLaikas.count();

        auto skirstymoPradzia = std::chrono::high_resolution_clock::now();
        skirstytiStudentus(testGrupe, nepazangus, normalus, galutinioBudas);
        auto skirstymoPabaiga = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> skirstymoLaikas = skirstymoPabaiga - skirstymoPradzia;
        programosLaikas += skirstymoLaikas.count();
        std::cout << failoPavadinimas <<": studentu skirstymas i 2 kategorijas uztruko " << std::fixed << std::setprecision(4) << skirstymoLaikas.count() << "s" << std::endl;
        std::cout << std::endl;

        auto rusiavimoPradzia = std::chrono::high_resolution_clock::now();
        rusiuotiOutput(normalus, rusiavimoBudas, galutinioBudas);
        
        auto rusiavimoPabaiga = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> rusiavimoLaikas = rusiavimoPabaiga - rusiavimoPradzia;
        std::cout  <<"Normaliu studentu rusiavimo laikas: " << std::fixed << std::setprecision(4) << rusiavimoLaikas.count() << "s" << std::endl;
        programosLaikas += rusiavimoLaikas.count();

        auto rusiavimoPradzia1 = std::chrono::high_resolution_clock::now();
        rusiuotiOutput(nepazangus, rusiavimoBudas, galutinioBudas);
        auto rusiavimoPabaiga1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> rusiavimoLaikas1 = rusiavimoPabaiga1 - rusiavimoPradzia1;
        std::cout  <<"Nepazangiu studentu rusiavimo laikas: " << std::fixed << std::setprecision(4) << rusiavimoLaikas1.count() << "s" << std::endl;
        programosLaikas += rusiavimoLaikas1.count();

        sortedStudentSpausdinimas(lowGradeFailas, highGradeFailas, nepazangus, normalus, galutinioBudas);
        
        testGrupe.clear();
        nepazangus.clear();
        normalus.clear();
        
        std::cout << std::endl << "Visas testavimo laikas: " << programosLaikas << "s" << std::endl << std::endl;

        programosLaikas = 0.0;
    }
}

void septintas(char galutinioBudas){

    std::cout << "TESTAI\n";
    std::cout << "----------------------------------------------\n";

    std::cout << "Move constructor test: \n";
    student originalus1("Jonas", "Jonaitis", {1, 2, 3, 4, 5}, 6);
    originalus1.skaiciuotiGalutini(galutinioBudas);
    std::cout << "Originalus studentas: \n" << originalus1;
    student kopija(std::move(originalus1));
    std::cout << "\nStudento kopija: " << kopija;

    std::cout << "----------------------------------------------\n";
    
    student originalus2("Jonas", "Jonaitis", {1, 2, 3, 4, 5}, 6);
    std::cout << "Move assigment test: \n";
    student other;
    originalus2.skaiciuotiGalutini(galutinioBudas);
    std::cout << "Originalus studentas: " << originalus2;
    other = originalus2;
    std::cout << "\nStudento kopija: " << other;

    std::cout << "----------------------------------------------\n";

    student originalus3("Jonas", "Jonaitis", {1, 2, 3, 4, 5}, 6);
    std::cout << "Copy constructor test: \n";
    originalus3.skaiciuotiGalutini(galutinioBudas);
    std::cout << "Originalus studentas: \n" << originalus3;
    student copy(originalus3);
    std::cout << "\nStudento kopija:" << copy;

    std::cout << "----------------------------------------------\n";

    std::cout << "Copy assigment test: \n";
    student kopija2;
    kopija2 = originalus3;
    originalus3.skaiciuotiGalutini(galutinioBudas);
    std::cout << "Originalus studentas: \n" << originalus3;
    std::cout << "\nStudento kopija: " << kopija;

    std::cout << "----------------------------------------------\n";
    std::cout << "Input test: \n";
    student s;
    std::cin >> s;
    s.skaiciuotiGalutini(galutinioBudas);
    std::cout << s;


    
}
void astuntas(){

    unsigned int sz = 1000;

    std::vector<int> v;
    Vector<int> v1;

    std::cout << "std::vector: \n";
    for(int i = 0; i < sz; ++i){
        v.push_back(i);
    }
    
    std::cout << "my vector: \n";
    for(int i = 0; i < sz; ++i){
        v1.push_back(i);
    }

    for(int i = 0; i < sz; ++i){
        std::cout << v[i];
        std::cout << "\n";
    }

    for(int i = 0; i < sz; ++i){
        std::cout << v1[i];
        std::cout << "\n";
    }

}