#include <iostream>
#include <fstream>
#include <string>
#include <glog/logging.h>

#include "parser.h"

int user_inerface(int& row, int& column) {
	std::cout << "Please enter the row:" << std::endl;
	std::cin >> row;
	std::cout << "Please enter the column:" << std::endl;
	std::cin >> column;

	if(row == -1 && column == -1) {
		std::cout << "QUIT is selected!" << std::endl;
		return 0;
	}
	std::cout << "row [" << row <<", "<< column <<"] is selected to display!";
	std::cout << std::endl;
	//TODO: error input, output complete row or colum.
	return 1;
}


int main(int argc, char** argv) {
	google::InitGoogleLogging(argv[0]);
	FLAGS_colorlogtostderr = true;  // Set log color
	FLAGS_logtostderr = true;

	//google::SetLogDestination(google::GLOG_INFO, "./log");
	LOG(INFO) << "initialize the file";
	LOG(WARNING) << "warn";
/*	std::ifstream in_file;
	std::string file_name = "./test.txt";
	in_file.open(file_name, std::ios::in);
	if(!in_file.good()) {
		std::cerr << "Failed to open file: " << file_name << std::endl;
		return 1;
	}*/

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
	ps.parse_line("5\tname\t3.14");
	std::cout << *ps.get_value<int>(0, 0) << std::endl;
	std::cout << ps.get_value<char>(1, 0) << std::endl;
	std::cout << *ps.get_value<float>(2, 0) << std::endl;

	google::ShutdownGoogleLogging();
    return 0;
}
