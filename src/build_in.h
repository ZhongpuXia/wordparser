
#ifndef _BUILD_IN_H_
#define _BUILD_IN_H_

#include <string>
#include <vector>

namespace parser {

void parse(std::string str, int& value);

void parse(std::string str, float& value);

void parse(std::string str, float& value);

void parse(std::string str, char** value);

void split(std::string str, std::string delimiter, std::vector<std::string>& sub_strs);

} // end of parser
#endif
