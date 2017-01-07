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

void parse(std::string str, char** value) {
	std::size_t len = str.length();

	char* temp = new char[len + 1];
	std::copy(str.begin(), str.end(), temp);
	temp[len] = '\0';
	*value = temp;

    return;
}

void split(std::string str, std::string delimiter, std::vector<std::string>& sub_strs) {
	std::size_t pos = 0;
	std::size_t found = 0;
	while (found != std::string::npos) {
	    found = str.find_first_of(delimiter, pos);
		if (found == pos) {
			pos += 1;
			continue;
		}
		sub_strs.emplace_back(str.substr(pos, found - pos));
		pos = found + 1;
	}

	return;
}

} // end of parser
