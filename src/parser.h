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
	void parse_line(const std::string& line);
    void parse_word(const std::string& word);

private:
    std::vector<std::string> _formats;
	std::vector<std::unique_ptr<void>> _values;
    std::vector<std::size_t> _values_size;
	std::string _delimiter;
	std::size_t _size_columns;

	std::vector<std::string> split(const std::string str, const std::string delimiter);

	template<class T>
	T get_type(std::size_t index);

};
} // end of parser

#endif
