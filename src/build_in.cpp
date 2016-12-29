#include <string>
#include <iostream>

#include "build_in.h"

namespace parser {

void parse(std::string str, int& value) {
    std::size_t len = str.length();
    if (0 == len) {
        std::cout << "[WARN] the input string is empty!" << std::endl;
        return;
    }

    std::string::size_type sz;
    value = std::stoi(str, &sz, 10);
    if (sz < len) {
        std::cout << "[WARN] character is contained in the string!" << std::endl;
    }

    return;
}

void parse(std::string str, float& value) {
    std::size_t len = str.length();
    if (0 == len) {
        std::cout << "[WARN] the input string is empty!" << std::endl;
        return;
    }

    std::string::size_type sz;
    value = std::stof(str, &sz);
    if (sz < len) {
        std::cout << "[WARN] character is contained in the string!" << std::endl;
    }

    return;
}

void parse(std::string str, double& value) {
    std::size_t len = str.length();
    if (0 == len) {
        std::cout << "[WARN] the input string is empty!" << std::endl;
        return;
    }

    std::string::size_type sz;
    value = std::stod(str, &sz);
    if (sz < len) {
        std::cout << "[WARN] character is contained in the string!" << std::endl;
    }

    return;
}

void parse(std::string str, const char* value) {
    value = str.data();
    std::cout << "function: " << value << std::endl;

    return;
}

} // end of parser
