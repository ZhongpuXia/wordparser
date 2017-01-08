#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <ostream>

#include "utils.h"
#include "user.h"

namespace parser {
class Parser {
public:
	explicit Parser(std::string formats);
	explicit Parser(std::string formats, std::string delimiter);
	void set_format(std::string formats);
	void parse_line(std::string line);

	//template<typename T>
    //void parse_word(std::string word, std::shared_ptr<void>& value_ptr, int& value_size);


	template<typename T>
	void parse_word(std::string word, std::shared_ptr<void>& value_ptr, int& value_size) {
		std::vector<std::string> word_vector;
		utils::split(word, ":", word_vector);
		std::vector<std::string> subwords;

		if (word_vector.size() < 2) {
			value_size = 1;
			subwords = word_vector;
		}
		else {
			utils::parse(word_vector[0], value_size);
			utils::split(word_vector[1], " ", subwords);
		}
		T* pv = new T[value_size];
		if (static_cast<int>(subwords.size()) != value_size) {
			std::cout << "[WARN]: ******!";
		}
		for (int i = 0; i < value_size; ++i) {
			T v;
			std::cout << i << "-subwords:" << subwords[i] << std::endl;
			utils::parse(subwords[i], v);
			pv[i] = v;
		}
		value_ptr = std::shared_ptr<void>(pv);

		return;
	}

	template<typename T>
	T* get_value(int row, int& size) {
		size = _values_size[row];
		T* value_ptr = static_cast<T*>(_values[row].get());
		return value_ptr;
	}

	//friend std::ostream& operator<<(std::ostream& out, const Parser parser);

private:
    std::vector<std::string> _formats;
	std::vector<std::shared_ptr<void> > _values;
    std::vector<int> _values_size;
	std::string _delimiter;
	int _columns_size;

	std::map<std::string, int> _format_map;
	void init_map();

};


} // end of parser

#endif
