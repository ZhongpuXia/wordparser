#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <ostream>
#include <glog/logging.h>

#include "utils.h"
#include "user.h"

namespace parser {

class Parser {
public:
    explicit Parser();
	explicit Parser(std::string delimiter);
	bool set_format(std::string formats);
	bool parse_line(std::string line);

    template<typename T>
    T* get_value(int row, int index);

    template<typename T>
    std::vector<T*> get_value(int row);

	//friend std::ostream& operator<<(std::ostream& out, const Parser parser);

private:
    enum Format {CHAR, INT, FLOAT, DOUBLE, USER};

    template<typename T>
    void parse_word(std::string word, int row);

    std::vector<std::vector<std::unique_ptr<void> > > _values;
	std::string _delimiter;
	int _columns_size;

    std::vector<enum Format> _formats;
    void init_format(std::string str);

};

template<typename T>
T* Parser::get_value(int row, int index) {
    if (row >= static_cast<int>(_values.size())) {
        LOG(ERROR) << "row = " << row << " out of range!";
        return nullptr;
    }
    if (index >= static_cast<int>(_values[row].size())) {
        LOG(ERROR) << "row = " << row << "index = " << index << " out of range!";
        return nullptr;
    }

    void* value_void = _values[row][index].get();
    T* value = static_cast<T*>(value_void);

    return value;
}

template<typename T>
std::vector<T*> Parser::get_value(int row) {
    std::vector<T*> array;
    if (row >= static_cast<int>(_values.size())) {
        LOG(ERROR) << "row = " << row << " out of range!";
        array.emplace_back(nullptr);
        return array;
    }

    for (int i = 0; i < static_cast<int>(_values[row].size()); ++i) {
        T* pv = get_value<T>(row, i);
        array.emplace_back(pv);
    }

    return array;
}

template<typename T>
void Parser::parse_word(std::string word, int row) {
    std::vector<std::string> word_vector = utils::split(word, ":");
    int array_size = 0;
    std::vector<std::string> subwords;

    if (word_vector.size() < 2) {
        array_size = 1;
        subwords = word_vector;
    }
    else {
        int* size = utils::parse<int>(word_vector[0]);
        array_size = *size;
        delete size;
        subwords = utils::split(word_vector[1], ",");
    }
    if (static_cast<int>(subwords.size()) != array_size) {
        LOG(ERROR) << "Wrong size! size = " << array_size << ", words size = " << subwords.size();
    }

    T* value_ptr = nullptr;
    for (int i = 0; i < static_cast<int>(subwords.size()); ++i) {
        value_ptr = utils::parse<T>(subwords[i]);
        _values[row].emplace_back(std::unique_ptr<void>(value_ptr));
    }

    return;
}

} // end of parser

#endif
