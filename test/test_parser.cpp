#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cmath>

#include "parser.h"
#include "utils.h"


TEST(Parser, ParserInt) {
	parser::Parser ps("int");
	ps.parse_line("5");
	int size = 0;
	int* value = ps.get_value<int>(0, size);
	EXPECT_EQ(5, *value);
	EXPECT_EQ(1, size);
}

TEST(Parser, ParserIntArray) {
	parser::Parser ps("int");
	ps.parse_line("2:5,6");
	int size = 0;
	int* value = ps.get_value<int>(0, size);
	EXPECT_EQ(5, value[0]);
	EXPECT_EQ(6, value[1]);
	EXPECT_EQ(2, size);
}

TEST(Parser, ParserFloat) {
	parser::Parser ps("float");
	ps.parse_line("3.1415");
	int size = 0;
	float* value = ps.get_value<float>(0, size);
	EXPECT_LE(fabs(3.1415 - *value), 1e-6);
	EXPECT_EQ(1, size);
}

TEST(Parser, ParserFloatArray) {
	parser::Parser ps("float");
	ps.parse_line("2:3.1415,2.7182");
	int size = 0;
	float* value = ps.get_value<float>(0, size);
	EXPECT_LE(fabs(3.1415 - value[0]), 1e-6);
	EXPECT_LE(fabs(2.7182 - value[1]), 1e-6);
	EXPECT_EQ(2, size);
}

TEST(Parser, ParseDouble) {
	parser::Parser ps("double");
	ps.parse_line("2.7182");
	int size = 0;
	double* value = ps.get_value<double>(0, size);
	EXPECT_EQ(2.7182, *value);
	EXPECT_EQ(1, size);
}

TEST(Parser, ParseDoubleArray) {
	parser::Parser ps("double");
	ps.parse_line("2:2.7182,3.1415");
	int size = 0;
	double* value = ps.get_value<double>(0, size);
	EXPECT_LE(fabs(2.7182 - value[0]), 1e-8);
	EXPECT_LE(fabs(3.1415 - value[1]), 1e-8);
	EXPECT_EQ(2, size);
}

/*TEST(Parser, ParseUser) {
	parser::Parser ps("User");
	ps.parse_line("0 Joe 18");
	int size = 0;
	utils::User* value = ps.get_value<utils::User>(0, size);
	std::string name = "Joe";

	EXPECT_EQ(0, value->id);
	EXPECT_EQ(0, name.compare(value->name));
	EXPECT_EQ(18, value->age);
}*/

/*TEST(Parser, ParseUserArray) {
	parser::Parser ps("double");
	ps.parse_line("2:2.7182 3.1415");
	int size = 0;
	double* value = ps.get_value<double>(0, size);
	EXPECT_LE(fabs(2.7182 - value[0]), 1e-8);
	EXPECT_LE(fabs(3.1415 - value[1]), 1e-8);
	EXPECT_EQ(2, size);
}

TEST(Parser, ParseChar) {
	parser::Parser ps("char");
	ps.parse_line("My name is Joe!");
	int size = 0;
	char* value = ps.get_value<char>(0, size);
	ASSERT_STREQ()
	EXPECT_EQ(2.7182, *value);
	EXPECT_EQ(1, size);
}


/*TEST(Parser, ParseChar) {
	parser::Parser ps("char");
	ps.parse_line("My name is Joe!");
	int size = 0;
	char* value = ps.get_value<char>(0, size);
	ASSERT_STREQ()
	EXPECT_EQ(2.7182, *value);
	EXPECT_EQ(1, size);
}

TEST(Parser, ParseCharArray){
	parser::Parser ps("char");
	ps.parse_line("4: My name is Joe!");
	int size = 0;
	double* value = ps.get_value<double>(0, size);
	EXPECT_LE(fabs(2.7182 - value[0]), 1e-8);
	EXPECT_LE(fabs(3.1415 - value[1]), 1e-8);
	EXPECT_EQ(4, size);
}*/


int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
