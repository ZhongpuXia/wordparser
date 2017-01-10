#include "parser.h"

namespace parser {

Parser::Parser(std::string formats) {
	_delimiter = "\t";
    set_format(formats);
}

Parser::Parser(std::string formats, std::string delimiter) {
	_delimiter = delimiter;
    set_format(formats);
}

bool Parser::set_format(std::string formats) {
    std::vector<std::string> fmts = utils::split(formats, _delimiter);
	_columns_size = static_cast<int>(_formats.size());
    _formats.resize(_columns_size);
    for (int i = 0; i < _columns_size; ++i) {
        if (fmts[i].compare("char") == 0) {
            _formats[i] = CHAR;
        }
        else if (fmts[i].compare("int") == 0 ) {
            _formats[i] = INT;
        }
        else if (fmts[i].compare("float") == 0 ) {
            _formats[i] = FLOAT;
        }
        else if (fmts[i].compare("double") == 0) {
            _formats[i] = DOUBLE;
        }
        else if (fmts[i].compare("User") == 0) {
            _formats[i] = USER;
        }
        else {
            LOG(ERROR) << "Wrong type: " << fmts[i];
            return false;
        }
    }
    return true;
}

bool Parser::parse_line(std::string line) {
    std::vector<std::string> words = utils::split(line, _delimiter);
	if (static_cast<int>(words.size()) > _columns_size) {
		LOG(ERROR) << "Wrong size of the lines!";
		return false;
	}
	for (int i = 0; i < static_cast<int>(words.size()); ++i) {
        enum Format fmt = _formats[i];
        std::vector<std::unique_ptr<void> > values_ptr;
		switch (fmt) {
            case CHAR:
                values_ptr = parse_word<char>(words[i]);
                break;
			case INT:
                values_ptr = parse_word<int>(words[i]);
                break;
			case FLOAT:
                values_ptr = parse_word<float>(words[i]);
                break;
			case DOUBLE:
                values_ptr = parse_word<double>(words[i]);
                break;
			case USER:
                values_ptr = parse_word<utils::User>(words[i]);
                break;
			default:
				LOG(ERROR) << "undefined type: [" << fmt <<"]";
                return false;
        }
		LOG(INFO) << "The " << i << "-th row is: " << _formats[i];
		_values.emplace_back(std::move(values_ptr));
	}
    return true;
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
