#include "user.h"

namespace parser {

std::ostream& operator<< (std::ostream& os, const User& user) {
    os << "id: " << user.id;
    os << "name: " << user.name;
    return os;
}

void parse(std::string str, User& user) {
    std::size_t len = str.length();
    if (0 == len) {
        std::cout << "[WARN] the input string is empty!" << std::endl;
        return;
    }

    std::string::size_type sz;
    user.id = std::stoi(str, &sz, 10);
    user.name = str.substr(sz).c_str();

    return;
}

} // end of parser
