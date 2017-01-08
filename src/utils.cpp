#include <string>
#include <iostream>
#include <glog/logging.h>

#include "utils.h"

namespace utils {

void parse(std::string str, int& value) {
    std::size_t len = str.length();
    if (0 == len) {
		LOG(WARNING) << "The string is empty, value = 0!";
		value = 0;
        return;
    }

    std::string::size_type sz;
    value = std::stoi(str, &sz, 10);
    if (sz == 0) {
		LOG(WARNING) << "No digit is included, value = 0!";
		value = 0;
	}
	else if (sz < len) {
		LOG(WARNING) << "Characters are included in the string!";
    }

    return;
}

void parse(std::string str, float& value) {
    std::size_t len = str.length();
    if (0 == len) {
		LOG(WARNING) << "The string is empty, value = 0!";
		value = 0.0;
        return;
    }

    std::string::size_type sz;
    value = std::stof(str, &sz);
    if (sz == 0) {
		LOG(WARNING) << "No digit is included, value = 0!";
		value = 0.0;
	}
    else if (sz < len) {
		LOG(WARNING) << "Characters are included in the string!";
    }

    return;
}

void parse(std::string str, double& value) {
    std::size_t len = str.length();
    if (0 == len) {
		LOG(WARNING) << "The string is empty, value = 0!";
		value = 0.0;
        return;
    }

    std::string::size_type sz;
    value = std::stod(str, &sz);
    if (sz == 0) {
		LOG(WARNING) << "No digit is included, value = 0!";
		value = 0.0;
	}
    else if (sz < len) {
		LOG(WARNING) << "Characters are included in the string!";
    }

    return;
}

void parse(std::string str, char*& value) {
	std::size_t len = str.length();

	value = new char[len + 1];
	std::copy(str.begin(), str.end(), value);
	value[len] = '\0';

    return;
}

void split(std::string str, std::string delimiter, std::vector<std::string>& sub_strs) {
	std::size_t pos = 0;
	std::size_t found = 0;
	sub_strs.clear();
	while (found != std::string::npos) {
	    found = str.find_first_of(delimiter, pos);
		if (found == pos) {
			LOG(INFO) << "Skip space.";
			pos += 1;
			continue;
		}
		sub_strs.emplace_back(str.substr(pos, found - pos));
		pos = found + 1;
	}

	return;
}

} // end of utils
