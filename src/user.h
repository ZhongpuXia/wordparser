#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <iostream>

namespace parser {

struct User {
    int id;
    const char* name;
};

void parse(std::string str, User& user);

} // end of parser

#endif
