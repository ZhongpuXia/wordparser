#include <iostream>
#include <fstream>
#include <string>
#include <glog/logging.h>

#include "parser.h"

int user_interface(int column_limit) {
    int column = 0;
    while (1) {
    	std::cout << "\n\ncolumn[0 ~ " << column_limit << "], ";
        std::cout << "-1: next row; -2: quit" << std::endl;
        std::cout << "Please input value: ";
	    std::cin >> column;
        if (column < column_limit && column > -3) {
            break;
        }
        std::cout << "Value is out of the range, Please input again!";
    }

	if (column == -2) {
		std::cout << "QUIT is selected!" << std::endl;
	}
    else if (column == -1) {
		std::cout << "Next row is selected!" << std::endl;
    }
    else {
        std::cout << column << "-th is selected to display!" << std::endl;
    }
	return column;
}


int main(int argc, char** argv) {
	google::InitGoogleLogging(argv[0]);
	FLAGS_colorlogtostderr = true;  // Set log color
	FLAGS_logtostderr = true;

    if (argc < 2) {
        LOG(ERROR) << "No file is input, exit(1)!";
        LOG(INFO) << "Run as: " << argv[0] << " file path";
        return 1;
    }

	std::ifstream in_file;
	std::string file_name(argv[1]);
	in_file.open(file_name, std::ios::in);
	if (!in_file.is_open()) {
		LOG(ERROR) << "Failed to open: " << file_name << ", exit(1)!" << std::endl;
	}

    parser::Parser parser("\t");
    char str_in[256];
    in_file.getline(str_in, 255, '\n');
    std::string head(str_in);
    if (!parser.set_format(head)) {
        LOG(ERROR) << "Title of file: " << str_in << "exit(1)!" << std::endl;
        return 1;
    }

    while (1) {
        in_file.getline(str_in, 255, '\n');
        if (!in_file.good()) {
            std::cout << "End of the file!" << std::endl;
            break;
        }

        std::string contents(str_in);
        parser.parse_row(contents);
        int column_size = parser.columns_size();

        int col_select = 0;
        while(1) {
            col_select = user_interface(column_size - 1);
            if (col_select > -1) {
              parser.print_column(col_select);
            }
            else {
                break;
            }
        }
        if (col_select == -2) {
            break;
        }
    }
    in_file.close();



    int* p_i = utils::parse<int>("11");
    float* p_f = utils::parse<float>("3.1415");
    char* p_name = utils::parse<char>("Jone");
    double* p_d = utils::parse<double>("3.1415926");
    double* p_d2 = utils::parse<double>("3.1415926");
    utils::User* p_user = utils::parse<utils::User>("0 Jone 15 40.5");


    std::cout << "int: " << (p_i ? std::to_string(*p_i) : "None") << std::endl;
    std::cout << "float: " << (p_f ? std::to_string(*p_f) : "None") << std::endl;
    std::cout << "char: " << (p_name ? p_name : "None") << std::endl;
    std::cout << "double: " << (p_d ? std::to_string(*p_d) : "None") << std::endl;
    std::cout << "double: " << (p_d2 ? std::to_string(*p_d2) : "None") << std::endl;
    std::cout << "user:" << p_user << std::endl;

    delete p_i;
    delete p_f;
	delete[] p_name;
    delete[] p_d;
    //delete p_user;

	parser::Parser ps("\t");
    ps.set_format("int\tchar\tfloat");
	ps.parse_row("5\tname\t3.14");
	std::cout << *ps.get_column<int>(0)[0] << std::endl;
	std::cout << ps.get_column<char>(1)[0] << std::endl;
	std::cout << *ps.get_column<float>(2)[0] << std::endl;
    ps.print_column(0);
    ps.print_column(1);
    ps.print_column(2);

	google::ShutdownGoogleLogging();
    return 0;
}
