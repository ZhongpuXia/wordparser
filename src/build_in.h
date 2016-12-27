
#ifndef _BUILD_IN_H_
#define _BUILD_IN_H_

#include <string>

namespace parser {

int parse(std::string str, int& value);

int parse(std::string str, float& value);

int parse(std::string str, const char* value);

} // end of parser
#endif
