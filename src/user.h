#ifndef _USER_UTILS_H_
#define _USER_UTILS_H_

#include <vector>
#include <string>
#include <memory>

#include "utils.h"

namespace utils {

struct User {
    int id;
    std::unique_ptr<char> name;
    int age;
    float weight;

    friend std::ostream& operator<< (std::ostream& out, const User* user);
};

template<>
User* parse<User>(std::string str);

} // end of utils

#endif
