
#ifndef _UTILS_BUILDIN_H__
#define _UTILS_BUILDIN_H__

#include <string>
#include <vector>
#include <typeinfo>
#include <glog/logging.h>

namespace utils {

template<typename T>
T* parse(std::string str) {
    if (typeid(char) != typeid(T)) {
        LOG(WARNING) << "Unknown type, convert to char*!";
    }

    std::size_t len = str.length();
    if (0 == len) {
		LOG(WARNING) << "The string is empty, return nullptr!";
        return nullptr;
    }
    T* p_value = new char[len + 1];
    std::copy(str.begin(), str.end(), p_value);
    p_value[len] = '\0';

    return p_value;
}

template<>
int* parse<int>(std::string str);

template<>
float* parse<float>(std::string str);

template<>
double* parse<double>(std::string str);

std::vector<std::string> split(std::string str, std::string delimiter);

} // end of utils
#endif
