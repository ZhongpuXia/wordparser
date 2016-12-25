#include <iostream>
#include <fstream>
#include <string>

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
	std::ifstream in_file;
	std::string file_name = "./test.txt";
	in_file.open(file_name, std::ios::in);
	if(!in_file.good()) {
		std::cerr << "Failed to open file: " << file_name << std::endl;
		return 1;
	}

	int row = 0;
	int column = 0;
	while(!user_inerface(row, column)) {

	}
}
