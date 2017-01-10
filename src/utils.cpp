#include "utils.h"

namespace utils {

template<>
int* parse<int>(std::string str) {
    std::size_t len = str.length();
    if (0 == len) {
		LOG(WARNING) << "The string is empty, return nullptr!";
        return nullptr;
    }
    std::string::size_type sz;
    int* p_value = new int;
    *p_value = std::stoi(str, &sz, 10);
    if (0 == sz) {
		LOG(WARNING) << "No digit is included, return nullptr!";
        delete p_value;
        p_value = nullptr;
    }
    if (sz < len) {
		LOG(WARNING) << "Characters are included in digits, return nullptr!";
        delete p_value;
        p_value = nullptr;
    }

    return p_value;
}

template<>
float* parse<float>(std::string str) {
    std::size_t len = str.length();
    if (0 == len) {
		LOG(WARNING) << "The string is empty, return nullptr!";
        return nullptr;
    }
    std::string::size_type sz;
    float* p_value = new float;
    *p_value = std::stof(str, &sz);
    if (0 == sz) {
		LOG(WARNING) << "No digit is included, return nullptr!";
        delete p_value;
        p_value = nullptr;
    }
    if (sz < len) {
		LOG(WARNING) << "Characters are included in digits, return nullptr!";
        delete p_value;
        p_value = nullptr;
    }

    return p_value;
}

template<>
double* parse<double>(std::string str) {
    std::size_t len = str.length();
    if (0 == len) {
		LOG(WARNING) << "The string is empty, return nullptr!";
        return nullptr;
    }
    std::string::size_type sz;
    double* p_value = new double;
    *p_value = std::stod(str, &sz);
    if (0 == sz) {
		LOG(WARNING) << "No digit is included, return nullptr!";
        delete p_value;
        p_value = nullptr;
    }
    if (sz < len) {
		LOG(WARNING) << "Characters are included in digits, return nullptr!";
        delete p_value;
        p_value = nullptr;
    }

    return p_value;
}

std::vector<std::string> split(std::string str, std::string delimiter) {
    std::vector<std::string> sub_strs;
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

	return sub_strs;
}

} // end of utils
