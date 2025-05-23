/**
 * @file functions.h
 * @author Narbas
 * @brief this file contains functions declarations
 * @version v2.0
 * @date 2025-05-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include "student.h"
#include "vector.h"

void rusiuotiOutput(Vector<student>& grupe, char rusiavimoBudas, char galutinioBudas);
void spausdinimasTerminale(const Vector<student>& grupe, char galutinioBudas);
void spausdinimasFaile(const Vector<student>& grupe, char galutinioBudas);
void generuotiFaila(int pKiekis, int studentuKiekis, const std::string& failoPavadinimas);
void spausdinimas(char spausBudas, char rusiavimoBudas, char galutinioBudas, Vector<student>&grupe);
void sortedStudentSpausdinimas(std::string lowGradeFailas, std::string highGradeFailas, Vector<student>&nepazangus, Vector<student>&normalus, char galutinioBudas);
void nuskaitytiGeneruotusFailus(const std::string& failoPavadinimas, Vector<student> & grupe, int pKiekis, char galutinioBudas);
void skirstytiStudentus(Vector<student> & grupe, Vector<student>& nepazangus, Vector<student>& normalus, char galutinioBudas);

void pirmas(Vector<student>& grupe, char spausBudas, char rusiavimoBudas, char galutinioBudas, int pKiekis);
void antras(Vector<student>& grupe, char spausBudas, char rusiavimoBudas, char galutinioBudas, int pKiekis);
void trecias(Vector<student>& grupe, const Vector<std::string>& vardai, const Vector<std::string>& pavardes, char spausBudas, char rusiavimoBudas, char galutinioBudas, int pKiekis);
void ketvirtas(Vector<student>& grupe, int pKiekis, char galutinioBudas);
void penktas(int pKiekis);
void sestas(Vector<student>& grupe, Vector<student>& testGrupe, Vector<student>& nepazangus, Vector<student>& normalus, char galutinioBudas, char rusiavimoBudas, int pKiekis);
void septintas(char galutinioBudas);
void astuntas();
#endif