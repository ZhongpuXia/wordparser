#include <glog/logging.h>
#include "user.h"
#include "utils.h"

namespace utils {

std::ostream& operator<< (std::ostream& out, const User& user) {
    out << " id=" << user.id;
    out << " name=" << user.name;
	out << " age=" << user.age;
    return out;
}

void parse(std::string str, User& user) {
    std::size_t len = str.length();
    if (0 == len) {
		LOG(WARNING) << "The string is empty, default value is set!";
		user.id = 0;
		user.name = "";
		user.age = 0;
        return;
    }

	std::vector<std::string> sub_strs;
	split(str, " ", sub_strs);
	if (3 != sub_strs.size()) {
		LOG(WARNING) << "Size of string is wrong, default value is set!";
		user.id = 0;
		user.name = "";
		user.age = 0;
        return;
	}
	parse(sub_strs[0], user.id);
	user.name = sub_strs[1];
	parse(sub_strs[2], user.age);
	LOG(INFO) << "Parse User:" << user;
    
	return;
}

} // end of utils
