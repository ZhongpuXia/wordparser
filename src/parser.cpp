#include "parser.h"

namespace parser {

Parser::Parser() {
    _delimiter = "\t";
}

Parser::Parser(std::string delimiter) {
	_delimiter = delimiter;
}

bool Parser::set_format(std::string formats) {
    std::vector<std::string> fmts = utils::split(formats, _delimiter);
	_columns_size = static_cast<int>(fmts.size());
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
    LOG(INFO) << "size of formats: " << _columns_size;
    return true;
}

bool Parser::parse_line(std::string line) {
    std::vector<std::string> words = utils::split(line, _delimiter);
	if (static_cast<int>(words.size()) > _columns_size) {
		LOG(ERROR) << "Wrong size of the lines!";
		return false;
	}
	for (int row = 0; row < static_cast<int>(words.size()); ++row) {
        enum Format fmt = _formats[row];
        std::vector<std::unique_ptr<void> > values_ptr;
        _values.resize(words.size());
		switch (fmt) {
            case CHAR:
                parse_word<char>(words[row], row);
                break;
			case INT:
                parse_word<int>(words[row], row);
                break;
			case FLOAT:
                parse_word<float>(words[row], row);
                break;
			case DOUBLE:
                parse_word<double>(words[row], row);
                break;
			case USER:
                parse_word<utils::User>(words[row], row);
                break;
			default:
				LOG(ERROR) << "undefined type: [" << fmt <<"]";
                return false;
        }
		LOG(INFO) << "The " << row << "-th columns is: " << words[row];
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
