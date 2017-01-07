#include "user.h"
#include "build_in.h"

namespace parser {

std::ostream& operator<< (std::ostream& out, const User& user) {
    out << " id=" << user.id;
    out << " name=" << user.name;
	out << " age=" << user.age;
    return out;
}

void parse(const std::string str, User& user) {
    std::size_t len = str.length();
    if (0 == len) {
        std::cout << "[WARN] the input string is empty!" << std::endl;
        return;
    }
	std::vector<std::string> sub_strs;
	split(str, " ", sub_strs);

	if (3 != sub_strs.size()) {
		std::cout << "[WARN] the input string is wrong!";
	}
	std::cout << sub_strs[0] << sub_strs[1] << sub_strs[2] << std::endl;
	parse(sub_strs[0], user.id);
	user.name = sub_strs[1];
	parse(sub_strs[2], user.age);
    
	return;
}

} // end of parser
