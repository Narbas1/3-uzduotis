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

void rusiuotiOutput(std::vector<student>& grupe, char rusiavimoBudas, char galutinioBudas);
void spausdinimasTerminale(const std::vector<student>& grupe, char galutinioBudas);
void spausdinimasFaile(const std::vector<student>& grupe, char galutinioBudas);
void generuotiFaila(int pKiekis, int studentuKiekis, const std::string& failoPavadinimas);
void spausdinimas(char spausBudas, char rusiavimoBudas, char galutinioBudas, std::vector<student>&grupe);
void sortedStudentSpausdinimas(std:: string lowGradeFailas, std::string highGradeFailas, std::vector<student>&nepazangus, std::vector<student>&normalus, char galutinioBudas);
void nuskaitytiGeneruotusFailus(const std::string& failoPavadinimas, std::vector<student> & grupe, int pKiekis, char galutinioBudas);
void skirstytiStudentus(std::vector<student> & grupe, std::vector<student>& nepazangus, std::vector<student>& normalus, char galutinioBudas);

void pirmas(std::vector<student>& grupe, char spausBudas, char rusiavimoBudas, char galutinioBudas, int pKiekis);
void antras(std::vector<student>& grupe, char spausBudas, char rusiavimoBudas, char galutinioBudas, int pKiekis);
void trecias(std::vector<student>& grupe, const std::vector<std::string>& vardai, const std::vector<std::string>& pavardes, char spausBudas, char rusiavimoBudas, char galutinioBudas, int pKiekis);
void ketvirtas(std::vector<student>& grupe, int pKiekis, char galutinioBudas);
void penktas(int pKiekis);
void sestas(std::vector<student>& grupe, std::vector<student>& testGrupe, std::vector<student>& nepazangus, std::vector<student>& normalus, char galutinioBudas, char rusiavimoBudas, int pKiekis);
void septintas(char galutinioBudas);
#endif