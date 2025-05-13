/**
 * @file student.cpp
 * @author Narbas
 * @brief this file contains class methods implementation
 * @version v2.0
 * @date 2025-05-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "student.h"
#include <algorithm>
#include <numeric>
#include <iomanip>

inline float student::skaiciuotiVid() const {
    if (pazymiai.empty()) return 0.0f;
    return std::accumulate(pazymiai.begin(), pazymiai.end(), 0.0f)
         / pazymiai.size();
}

float student::skaiciuotiMed() const {
    if (pazymiai.empty()) return 0.0f;
    auto copy = pazymiai;
    auto mid  = copy.size() / 2;
    std::nth_element(copy.begin(), copy.begin() + mid, copy.end());
    float m = copy[mid];
    if (copy.size() % 2 == 0) {
        std::nth_element(copy.begin(), copy.begin() + mid - 1, copy.end());
        m = (m + copy[mid - 1]) / 2.0f;
    }
    return m;
}

inline void student::skaiciuotiGalutini(char galutinioBudas) {
    if (galutinioBudas == 'v') {
        galutinisV = skaiciuotiVid() * 0.4f + egzaminoRezultatas * 0.6f;
    }
    else{
        galutinisM = skaiciuotiMed() * 0.4f + egzaminoRezultatas * 0.6f;
    }
}

std::ostream& operator << (std::ostream& os, const student& studentas){
    os << "Vardas: " << studentas.getVardas() << "\n" << "Pavarde: " << studentas.getPavarde() << "\n";
    for(auto p : studentas.pazymiai){
        os << p << " ";
    }
    os << "\nEgzaminas: " << studentas.getEgzaminoRezultatas() << "\n";

    if(studentas.galutinisM != 0){
        os << "Galutinis(M): " << studentas.getGalutinisM() << "\n"; 
    }
    else{
        os << "Galutinis(V): " << studentas.getGalutinisV() << "\n";
    }

    return os;
}
std::istream& operator >> (std::istream& in, student& studentas){

    std::string v, pav;
    int p, e;
    float pazymys;
    std::cout << "Pazymiu kiekis: " << "\n";
    in >> p;
    studentas.pazymiai.clear();
    studentas.pazymiai.reserve(p);

    std::cout << "Vardas: ";
    in >> v; 
    studentas.setVardas(v);
    std::cout << "Pavarde: ";
    in >> pav; 
    studentas.setPavarde(pav);
    std::cout << "\n";
    std::cout << "Pazymiai: ";
    for(int i = 0; i < p; i++){
        in >> pazymys;
        studentas.addPazymys(pazymys);
    }
    std::cout << "\n";
    std::cout << "Egzamino pazymys: ";
    in >> e;
    studentas.setEgzaminoRezultatas(e);
    
    return in;
}