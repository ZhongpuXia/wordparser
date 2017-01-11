#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>
#include <glog/logging.h>

#include "utils.h"
#include "user.h"

namespace parser {

class Parser {
public:
    explicit Parser();
	explicit Parser(std::string delimiter);
	bool set_format(std::string formats);
	bool parse_row(std::string row);

    int columns_size(){
        return _columns_size;
    }

    template<typename T>
    std::vector<T*> get_column(int col);

    void print_column(int col);

private:
    enum Format {CHAR, INT, FLOAT, DOUBLE, USER};
    std::vector<enum Format> _formats;

    template<typename T>
    void parse_column(std::string column, int col);

    std::vector<std::vector<std::unique_ptr<void> > > _values;
	std::string _delimiter;
	int _columns_size;
};

template<typename T>
std::vector<T*> Parser::get_column(int col) {
    std::vector<T*> array;
    if (col >= static_cast<int>(_values.size())) {
        LOG(ERROR) << "column = " << col << " out of range, empty vector returns!";
        array.clear();
        return array;
    }

    array.resize(_values[col].size());
    for (int i = 0; i < static_cast<int>(_values[col].size()); ++i) {
        void* p_void = _values[col][i].get();
        T* pv = static_cast<T*>(p_void);
        array[i] = pv;
    }

    return array;
}

template<typename T>
void Parser::parse_column(std::string column, int col) {
    std::vector<std::string> sub_column = utils::split(column, ":");
    int array_size = 0;
    std::vector<std::string> words;

    if (sub_column.size() < 2) {
        array_size = 1;
        words = sub_column;
    }
    else {
        int* size = utils::parse<int>(sub_column[0]);
        array_size = *size;
        delete size;
        words = utils::split(sub_column[1], ",");
    }
    if (static_cast<int>(words.size()) != array_size) {
        LOG(ERROR) << "Wrong size! size = " << array_size << ", words size = " << words.size();
    }

    T* value_ptr = nullptr;
    for (int i = 0; i < static_cast<int>(words.size()); ++i) {
        value_ptr = utils::parse<T>(words[i]);
        _values[col].emplace_back(std::unique_ptr<void>(value_ptr));
    }

    return;
}

} // end of parser

#endif
