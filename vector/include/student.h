#ifndef STUDENT_H
#define STUDENT_H

/**
 * @file student.h
 * @author Narbas
 * @brief this file contains Human and Student classes
 * @version v2.0
 * @date 2025-05-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <vector>
#include <string>
#include <iostream>
#include "../include/vector.h"
class Human{
    protected:

        std::string vardas;
        std::string pavarde;

    public:

    Human() : vardas(""), pavarde("") {}
    Human(const std::string& v, const std::string& p) : vardas(v), pavarde(p) {}

    //getters
    const std::string& getVardas() const { return vardas; }
    const std::string& getPavarde() const { return pavarde; }
    //setters
    void setVardas(const std::string& v)   { vardas = v; }
    void setPavarde(const std::string& p)  { pavarde = p; }

    virtual ~Human() = default;

    virtual void skaiciuotiGalutini(char galutinioBudas) = 0;

};
    
class student : public Human{

    private:
        
        Vector<float> pazymiai{};
        float egzaminoRezultatas = 0.0f;
        float galutinisM = 0.0f;
        float galutinisV = 0.0f;

    public:

    student() = default;

    //rule of 5-----------------------------------------------------
    //copy
    student(const student &other) noexcept : Human(other.getVardas(), other.getPavarde()), pazymiai(other.pazymiai), 
                                    egzaminoRezultatas(other.egzaminoRezultatas), galutinisM(other.galutinisM), galutinisV(other.galutinisV){};
    //copy asg
    student& operator=(const student &other) noexcept {
        if(this != &other){
            setVardas(other.getVardas());
            setPavarde(other.getPavarde());
            pazymiai = other.pazymiai;
            egzaminoRezultatas = other.egzaminoRezultatas;
            galutinisM = other.galutinisM;
            galutinisV = other.galutinisV;
        }

        return *this;
    };
    //move
    student(student &&other) noexcept : Human(std::move(other.vardas), std::move(other.pavarde)),
      pazymiai(std::move(other.pazymiai)),
      egzaminoRezultatas(other.egzaminoRezultatas), 
      galutinisM(other.galutinisM), 
      galutinisV(other.galutinisV) {}
    //move asg
    student& operator=(student &&other) noexcept {
        if(this != &other){
            vardas = std::move(other.vardas);
            pavarde = std::move(other.pavarde);
            pazymiai = std::move(other.pazymiai);
            egzaminoRezultatas = other.egzaminoRezultatas;
            galutinisM = other.galutinisM;
            galutinisV = other.galutinisV;
        }
        return *this;
    };
    // -------------------------------------------------------------

    //isvestis, ivestis overloads
    friend std::ostream& operator << (std::ostream& os, const student& studentas);
    friend std::istream& operator >> (std::istream& in, student& studentas);

    //parametrizuotas ctor
    student(std::string v, std::string p, Vector<float> pazymiai, float egz) noexcept : Human(v, p), pazymiai(std::move(pazymiai)), egzaminoRezultatas(egz) {}

    //setters
    void setPazymiai(Vector<float> paz) noexcept{ pazymiai = std::move(paz); }
    void setEgzaminoRezultatas(float egz) noexcept { egzaminoRezultatas = egz; }
    void setGalutinisV(float V) noexcept { galutinisV = V; }
    void setGalutinisM(float M) noexcept { galutinisM = M; }

    //getters
    const Vector<float>& getPazymiai() const { return pazymiai; }
    float getEgzaminoRezultatas() const { return egzaminoRezultatas; }
    float getGalutinisV() const { return galutinisV; }
    float getGalutinisM() const { return galutinisM; }

    //methods
    float skaiciuotiVid() const;
    float skaiciuotiMed() const;
    void skaiciuotiGalutini(char galutinioBudas) override;
    void addPazymys(float pazymys) { pazymiai.push_back(pazymys); }
};

std::ostream& operator<<(std::ostream& os, const student& studentas);
std::istream& operator>>(std::istream& in, student& studentas);

#endif