#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <memory>
#include <iostream>

namespace parser {

struct User {
    int id;
	std::string name;
	int age;

    friend std::ostream& operator<< (std::ostream& out, const User& user);
};

void parse(const std::string str, User& user);

} // end of parser

#endif
