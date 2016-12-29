#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>

#include "build_in.h"
#include "user.h"

namespace parser {
class Parser {
public:
	explicit void Parser(const std::string& column_types);
	explicit void Parser(const std::string& column_types, std::string delimiter);
	parse_line();

private:
    std::vector<std::string> _types;
	std::string _delimiter;

	std::vector<std::string> split(const std::string str, const std::string delimiter);

	template<class T>
	T get_type(std::size_t index);

};
} // end of parser

#endif
