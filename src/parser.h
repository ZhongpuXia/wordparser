#include <string>

#ifndef __PARSER_H__
#define __PARSER_H__

namespace parser {
class Parser {
public:
	Parser();
	parse_line();

private:
	parse(char* str, int& value);
	parse(char* str, float& value);
	parse(char* str, std::String& value);


};// end of class
} // end of namespace

#endif
