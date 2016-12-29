#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>

#include "build_in.h"
#include "user.h"

namespace parser {
class Parser {
public:
	explicit void Parser(std::string columns_type);
	parse_line();

private:
    std::vector<std::string> _types;

};
} // end of parser

#endif
