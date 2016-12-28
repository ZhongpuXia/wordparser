
#ifndef _BUILD_IN_H_
#define _BUILD_IN_H_

#include <string>

namespace parser {

void parse(std::string str, int& value);

void parse(std::string str, float& value);

void parse(std::string str, float& value);

void parse(std::string str, const char* value);

} // end of parser
#endif
