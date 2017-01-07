#include "parser.h"

namespace parser {

void Parser::init_map() {
	_format_map["int"] = 0;
	_format_map["float"] = 1;
	_format_map["double"] = 2;
	_format_map["char"] = 3;
	_format_map["User"] = 4;
}

Parser::Parser(const std::string& formats) {
	_delimiter = "\t";
	_formats = split(formats, _delimiter);
	_columns_size = _formats.size();
}

Parser::Parser(const std::string& formats, std::string delimiter) {
	_delimiter = delimiter;
	_formats = split(formats, delimiter);
	_columns_size = _formats.size();
}

void Parser::set_format(const std::string& formats) {
	_formats = split(formats, _delimiter);
}

void Parser::parse_line(const std::string& line) {
    std::vector<std::string> words = split(line, _delimiter);
	if (words.size() != _columns_size) {
		std::cout << "[Error] the size  is different from";
		return;
	}
	for (std::size_t i = 0; i < _columns_size; ++i) {
		std::string fmt = _formats[i];
        std::size_t sz;
		switch (_format_map[fmt]) {
			case _format_map["int"]: 
				int* value_ptr = nullptr;
				parse_word(words[i], value_ptr, sz);
				break;
			case _format_map["float"]: 
                float* value_ptr = nullptr;
                parse_word(words[i], value_ptr, sz);
				break;
			case _format_map["double"]: 
                double* value_ptr = nullptr;
                parse_word(words[i], value_ptr, sz);
				break;
			case _format_map["char"]: 
                char* value_ptr = nullptr;
                parse_word(words[i], value_ptr, sz);
                break;
			case _format_map["User"]: 
                User* value_ptr = nullptr;
				parse_word(words[i], value_ptr, sz);
				break;
			default: 
			    std::cout << "undefined type: [" << fmt <<"], the type is string at default" << std::endl;
        }
		_values.emplace_back(std::static_cast<void*>(value_ptr));
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
	    parse(word_vector[0], std::static_cast<int>(size));
        values = new T[size];
	    std::vector<T> subwords = split(word_vector[1], ' ');
        if (subwords.size() != size) {
			std::cout << "[WARN]: ******!";
        }
        for (std::size_t i = 0; i < size; ++i) {
            parse(subwords[i], values[i]);
        }
    }
	return;
}

std::ostream& operator<< (std::ostream out, const Parser parser) {
	for (std::size_t i = 0; i < parser._columns_size; ++i) {
		switch (parser._format_map[_formats[i]]) {
			case parser._format_map["int"]:
				int *p_value = std::static_cast<int*> parser._values[i];
				out << "int: ";
			case parser._format_map["float"]:
				float *p_value = std::static_cast<float*> parser._values[i];
				out << "float: ";
			case parser._format_map["double"]:
				double *p_value = std::static_cast<double*> parser._values[i];
				out << "double: ";
			case parser._format_map["char"]:
				char *p_value = std::static_cast<char*> parser._values[i];
				out << "char: ";
			case parser._format_map['User']:
				User* p_value = std::static<User*> parser._values[i];
				out << "User: ";
			default:
				out << "It is not a default format";
		}
		for (std::size_t j = 0; j < parser._values_size[i]; ++j) {
			out << p_value[j] << " ";
		}
		out << "\n";
	}
	return out;
}


} //end of parser
