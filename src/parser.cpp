#include "parser.h"

#include <memory>

namespace parser {

void Parser::Parser(const std::string& formats) {
	_delimiter = '\t';
	_formats = split(formats, _delimiter);
	_size_columns = _formats.size();
}

void Parser::Parser(const std::string& formats, std::string delimiter) {
	_delimiter = delimiter;
	_formats = split(formats, delimiter);
	_size_columns = _formats.size();
}

void set_format(const std::string& formats) {
	_formats = split(formats, _delimiter);
}

void Parser::parse_line(const std::string& str) {
    std::vector<std::string> contents = split(str, _delimiter);
	if (contents.size() != _size_columns) {
		std::cout << "[Error] the size  is different from";
		return;
	}
	for (int i = 0; i < _size_columns; ++i) {
		std::string fmt = _formats[i];
		switch(fmt) {
			case "int": {
				std::unique_ptr<int> value(new int);
				parse(contents[i], value);
				break;
			}
			case "float": {
				std::unique_ptr<float> value(new float);
				parse(contents[i], value)
				break;
			}
			case "double": {
				std::unique_ptr<double> value(new double);
				parse(contents[i], value);
				break;
			}
			case "char": {
				std::unique_ptr<char> value(new char);
				parse(contents[i], value);
				break;
			}
			case "User": {
				std::unique_ptr<User> value(new User);
				parse(contents[i], value);
				break;
			}
			default: {
			    std::cout << "undefined type: [" << type_str <<"], the type is string at default" << std::endl;
			    std::string result;
			    return result;
			}
		}
		std::shared_ptr<void> v = std::dynamic_pointer_cast<void>(value);
		_values.push_back(v);
	}
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
std::vector<T> parse(std::string str) {
	std::vector<std::string> str_vector = split(str, ':');
	T value;
	std::vector<T> values;
	if (str_vector.size() < 2) {
		parse(str, value);
		values.emplace_back(value);
		return values;
	}
	int num = 0;
	parse(str_vector[0], num);
	std::vector<T> str_contents = split(str_vector[1], ' ');
	for ( auto it = str_contents.begin(), it != str_contents.end(), ++it) {
		parse(*it, value);
		values.emplace_back(value);
	}
	if (values.size() != num) {
		print("[WARN]: ******!")
	}

	return values;
}

} //end of parser
