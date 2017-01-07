#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <ostream>

#include "build_in.h"
#include "user.h"

namespace parser {
class Parser {
public:
	explicit Parser(const std::string& formats);
	explicit Parser(const std::string& format, std::string delimiter);
	void set_format(const std::string& formats);
	void parse_line(const std::string& line);

	template<class T>
    void parse_word(const std::string& word, T* values, std::size_t& size);

	friend std::ostream& operator<<(std::ostream& out, const Parser parser);

private:
    std::vector<std::string> _formats;
	std::vector<std::shared_ptr<void> > _values;
    std::vector<std::size_t> _values_size;
	std::string _delimiter;
	std::size_t _columns_size;

	std::map<std::string, int> _format_map;
	void init_map();

	std::vector<std::string> split(const std::string str, const std::string delimiter);

};
} // end of parser

#endif
