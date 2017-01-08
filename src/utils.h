
#ifndef _UTILS_H__
#define _UTILS_H__

#include <string>
#include <vector>

namespace utils {

void parse(std::string str, int& value);

void parse(std::string str, float& value);

void parse(std::string str, double& value);

void parse(std::string str, char*& value);

void split(std::string str, std::string delimiter, std::vector<std::string>& sub_strs);

} // end of utils
#endif
