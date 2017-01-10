INTRODUCTION
    Prequirement:
        1. please install: cmake libgtest-dev lib-google-glog-dev
        2. make sure "libgtest.a libglog.a" in directory: /usr/lib/x86_64-linux-gnu/

    Implemention:
        1. parse build_in types and user-defined types in utils.h/utils.h and user.h/user.cpp, respectively;
        2. The types is implemented by template function: T*  parse<T>(std::string str) //new T[] to save values;
        3. In order to save values with different types and different length, it converts pointer in void* and saves value by std::vector<std::vector<std::unique<void>>>;
        4. std::unique_ptr is used to manage the new allocated memory;
        5. get the value by the void pointer and convert it into corresponding type;

    Special Case:
        1. If input formats are undefined, Parser::set_format() return false;
        2. If input string is longer than formats, Parser::parse_line() return false;
        3. It will return null pointer when failing to parser, such as: empty string, characters included in digits, missing substring in struct.

RUN

    1. cmake ..
    2. make
    3. make test
