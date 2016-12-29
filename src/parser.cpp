#include "parser.h"


namespace parser {

void Parser::Parser(const std::string& column_types) {
	_delimiter = '\t';
	_types = split(column_types, _delimiter);
}

void Parser::Parser(const std::string& column_types, std::string delimiter{
	_delimiter = delimiter;
	_types = split(column_types, delimiter);
}

void Parser::parse_line(const std::string& str) {
    std::vector<std::string> contents = split(str, _delimiter);

}


std::vector<std::string> Parser::split(const std::string str, const std::string delimiter) {
	std::size_t pos = 0;
	std::size_t found = 0;
	std::vector<std::string> str_vector;
	while (pos != std::string::npos) {
	    found = str.find_first_of(delimiter);
		str_vector.emplace_back(str.substr(pos, found - pos));
		pos = found;
	}

	return str_vector;
}

template<class T>
T get_type(std::size_t index) {
	type_str = _types[index];
	switch(type_str) {
		case "int": {
			int result = 0;
			return result;
		}
		case "float": {
			float result = 0.0;
			return result;
		}
		case "double": {
			double result = 0.0;
			return result;
		}
		case "char*": {
			char* result = '\0';
			return result;
		}
		case "User": {
			User result;
			return result;
		}
		default: {
			std::cout << "undefined type: [" << type_str <<"], the type is string at default" << std::endl;
			std::string result;
			return result;
		}
}
} //end of parser
