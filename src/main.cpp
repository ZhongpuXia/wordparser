#include <iostream>
#include <fstream>
#include <string>

#include "build_in.h"
#include "user.h"

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


int main() {
/*	std::ifstream in_file;
	std::string file_name = "./test.txt";
	in_file.open(file_name, std::ios::in);
	if(!in_file.good()) {
		std::cerr << "Failed to open file: " << file_name << std::endl;
		return 1;
	}*/

	int row = 0;
	float column = 0;
	char* name;
	parser::User user = {1, "Joe", 15};
    parser::parse("11", row);
    parser::parse("1.12", column);
    std::cout << "int:" << row << std::endl;
    std::cout << "float:" << column << std::endl;
    
	parser::parse("name", &name);
    std::cout << "char:" << name << std::endl;

	std::cout << user << std::endl;
	parser::parse("2 Lucy 15", user);
	std::cout << "user: " << user << std::endl;

	delete[] name;


    return 1;
}
