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
	_formats.clear();
	split(formats, _delimiter, _formats);
	_columns_size = _formats.size();
	init_map();
}

Parser::Parser(const std::string& formats, std::string delimiter) {
	_delimiter = delimiter;
	_formats.clear();
	split(formats, delimiter, _formats);
	_columns_size = _formats.size();
	init_map();
}

void Parser::set_format(const std::string& formats) {
	_formats.clear();
	split(formats, _delimiter, _formats);
}

void Parser::parse_line(const std::string& line) {
    std::vector<std::string> words;
	split(line, _delimiter, words);
	if (static_cast<int>(words.size()) != _columns_size) {
		std::cout << "[Error] the size  is different from";
		return;
	}
	for (int i = 0; i < _columns_size; ++i) {
		int value_size = 0;
		std::shared_ptr<void> value_ptr(nullptr);
		std::cout << i << ":" << words[i] << std::endl;
		
		switch (_format_map[_formats[i]]) {
			std::cout << _format_map[_formats[i]] << std::endl;
			case 0: 
				parse_word<int>(words[i], value_ptr, value_size);
				std::cout << "value:" << *((int*) value_ptr.get()) << "value_size:" << value_size;
				break;
			case 1: 
                parse_word<float>(words[i], value_ptr, value_size);
				break;
			case 2: 
                parse_word<double>(words[i], value_ptr, value_size);
				break;
			case 3: 
                parse_word<char*>(words[i], value_ptr, value_size);
                break;
			case 4: 
				parse_word<User>(words[i], value_ptr, value_size);
				break;
			default: 
			    std::cout << "undefined type: [" << _formats[i] <<"], the type is string at default" << std::endl;
        }

		_values.emplace_back(value_ptr);
        _values_size.push_back(value_size);
	}
}

/*std::ostream& operator<< (std::ostream out, const Parser parser) {
	for (int i = 0; i < parser._columns_size; ++i) {
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
		for (int j = 0; j < parser._values_size[i]; ++j) {
			out << p_value[j] << " ";
		}
		out << "\n";
	}
	return out;
}*/


} //end of parser 
