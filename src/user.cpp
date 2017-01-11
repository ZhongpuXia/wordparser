#include <glog/logging.h>
#include "user.h"
#include "utils.h"

namespace utils {

std::ostream& operator<< (std::ostream& out, const User& user) {
    out << " id=" << user.id;
    out << ", name=" << (user.name).get();
    out << ", age=" << user.age;
    out << ", weight=" << user.weight;

    return out;
}

template<>
User* parse<User>(std::string str) {
    std::size_t len = str.length();
    if (0 == len) {
		LOG(WARNING) << "The string is empty, return nullptr!";
        return nullptr;
    }
    std::vector<std::string> sub_strs = split(str, " ");
    if (4 != sub_strs.size()) {
		LOG(WARNING) << "Size of the string is wrong, default is assigned!";
        return nullptr;
    }

    int* p_id = parse<int>(sub_strs[0]);
    char* p_name = parse<char>(sub_strs[1]);
    int* p_age = parse<int>(sub_strs[2]);
    float* p_weight = parse<float>(sub_strs[3]);

    if (!(p_id && p_name && p_age && p_weight)) {
        LOG(WARNING) << "Failed to paser user, return nullptr!";
        return nullptr;
    }

    User* p_user = new User;
    p_user->id = *p_id;
    p_user->name = std::unique_ptr<char>(p_name);
    p_user->age = *p_age;
    p_user->weight = *p_weight;
    delete p_id;
    delete p_age;
    delete p_weight;

    return p_user;
}

} // end of utils
