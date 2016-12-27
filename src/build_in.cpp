#include <sstream>
#include "build_in.h"

namespace parser {
    int parse(std::string str, int& value) {
        std::stringstream sstr(str);
        sstr >> value;

        return 0;
    }

    int parse(std::string str, float& value) {
        std::stringstream sstr(str);
        sstr >> value;

        return 0;
    }

    int parse(std::string str, const char* value) {
        value = str.c_str();

        return 0;
    }
} // end of parser
