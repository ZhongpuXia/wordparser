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

void Parser::set_format(const std::string& formats) {
	_formats = split(formats, _delimiter);
}

void Parser::parse_line(const std::string& line) {
    std::vector<std::string> words = split(line, _delimiter);
	if (words.size() != _size_columns) {
		std::cout << "[Error] the size  is different from";
		return;
	}
	for (int i = 0; i < _size_columns; ++i) {
		std::string fmt = _formats[i];
        std::size_t sz;
		switch(fmt) {
			case "int": {
				int* value_ptr = nullptr;
				parse_word(words[i], value_ptr, sz);
				break;
			}
			case "float": {
                float* value_ptr = nullptr;
                parse_word(words[i], value_ptr, sz);
				break;
			}
			case "double": {
                double* value_ptr = nullptr;
                parse_word(words[i], value_ptr, sz);
				break;
			}
			case "char": {
                char* value_ptr = nullptr;
                parse_word(words[i], value_ptr, sz);
                break;
			}
			case "User": {
                User* value_ptr = nullptr;
				parse_word(words[i], value_ptr, sz);
				break;
			}
			default: {
			    std::cout << "undefined type: [" << type_str <<"], the type is string at default" << std::endl;
			    std::string result;
			    return result;
			}
        }
        std::unique_ptr<void> vp((void*)value_ptr);
		_values.push_back(vp);
        _values_size.push_back(sz);
	}
}


template<class T>
void parse_word(std::string word, T* values, std::size_t& size) {
	std::vector<std::string> word_vector = split(word, ':');

	if (word_vector.size() < 2) {
        size = 1;
        T value;
		parse(word, value);
        values = new T(value);
	}
    else {
	    parse(word_vector[0], (int)size);
        values = new T[size];
	    std::vector<T> subwords = split(word_vector[1], ' ');
        if (subwords.size() != size) {
            print("[WARN]: ******!")
        }
        for (std::size_t i = 0; i < size; ++i) {
            parse(subwords[i], values[i]);
        }
    }
	return;
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

} //end of parser
