#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <memory>
#include <iostream>

namespace utils {

struct User {
    int id;
	std::string name;
	int age;

    friend std::ostream& operator<< (std::ostream& out, const User& user);
};

void parse(std::string str, User& user);

} // end of utils

#endif
