#include "parser.h"

namespace parser {

Parser::Parser() {
    _delimiter = "\t";
}

Parser::Parser(std::string delimiter) {
	_delimiter = delimiter;
}

bool Parser::set_format(std::string formats) {
    std::vector<std::string> columns = utils::split(formats, _delimiter);
	_columns_size = static_cast<int>(columns.size());
    _formats.resize(_columns_size);
    for (int i = 0; i < _columns_size; ++i) {
        if (columns[i].compare("char") == 0) {
            _formats[i] = CHAR;
        }
        else if (columns[i].compare("int") == 0 ) {
            _formats[i] = INT;
        }
        else if (columns[i].compare("float") == 0 ) {
            _formats[i] = FLOAT;
        }
        else if (columns[i].compare("double") == 0) {
            _formats[i] = DOUBLE;
        }
        else if (columns[i].compare("User") == 0) {
            _formats[i] = USER;
        }
        else {
            LOG(ERROR) << "Wrong type: " << columns[i];
            return false;
        }
    }
    LOG(INFO) << "size of formats: " << _columns_size;
    return true;
}

bool Parser::parse_row(std::string row) {
    std::vector<std::string> columns = utils::split(row, _delimiter);
	if (static_cast<int>(columns.size()) > _columns_size) {
		LOG(ERROR) << "Wrong size of the rows!";
		return false;
	}
	for (int col = 0; col < static_cast<int>(columns.size()); ++col) {
        enum Format fmt = _formats[col];
        _values.resize(columns.size());
		switch (fmt) {
            case CHAR:
                parse_column<char>(columns[col], col);
                break;
			case INT:
                parse_column<int>(columns[col], col);
                break;
			case FLOAT:
                parse_column<float>(columns[col], col);
                break;
			case DOUBLE:
                parse_column<double>(columns[col], col);
                break;
			case USER:
                parse_column<utils::User>(columns[col], col);
                break;
			default:
				LOG(ERROR) << "undefined type: [" << fmt <<"]";
                return false;
        }
		LOG(INFO) << "The " << col << "-th columns is: " << columns[col];
	}
    return true;
}

void Parser::print_column(int col) {
    if (col >= static_cast<int>(_values.size())) {
        std::cout << "column: " << col << "out of range:" << _values.size() << std::endl;
    }
    std::cout << "The " << col <<"-th column:";
    for (size_t i = 0; i < _values[col].size(); ++i) {
        void* p_void = _values[col][i].get();
        if (p_void == nullptr) {
            std::cout << "None" << "\t";
            continue;
        }
		switch (_formats[i]) {
            case CHAR:
                std::cout << static_cast<char*>(p_void) << "\t";
                break;
			case INT:
                std::cout << *static_cast<int*>(p_void) << "\t";
                break;
			case FLOAT:
                std::cout << *static_cast<float*>(p_void) << "\t";
                break;
			case DOUBLE:
                std::cout << *static_cast<double*>(p_void) << "\t";
                break;
			case USER:
                std::cout << *static_cast<utils::User*>(p_void) << "\t";
                break;
        }
    }
    std::cout << std::endl;

    return;
}

} //end of parser
