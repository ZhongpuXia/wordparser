#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>

#include "build_in.h"
#include "user.h"

namespace parser {
class Parser {
public:
	explicit void Parser(const std::string& formats);
	explicit void Parser(const std::string& format, std::string delimiter);
	void set_format(const std::string& formats)
	parse_line();

private:
    std::vector<std::string> _formats;
	std::vector<std::unique_ptr<void>> _values;
	std::string _delimiter;
	std::size_t _size_columns;

	std::vector<std::string> split(const std::string str, const std::string delimiter);

	template<class T>
	T get_type(std::size_t index);

};
} // end of parser

#endif
