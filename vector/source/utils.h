#ifndef UTILS_H
#define UTILS_H

/**
 * @file utils.h
 * @author Narbas
 * @brief this file contains templates
 * @version v2.0
 * @date 2025-05-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <limits>
#include <string>

template<typename T>
T tikrintiInput(const std::string& prompt, const std::string& klaida) {
    T value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (!std::cin.fail()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cerr << klaida << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

#endif
