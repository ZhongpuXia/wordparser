#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cmath>

#include "parser.h"
#include "utils.h"

TEST(Parser, ParserInit) {
	parser::Parser ps;

    EXPECT_TRUE(ps.set_format("int\tchar\tfloat\tdouble\tUser"));
    EXPECT_FALSE(ps.set_format("long"));
    EXPECT_FALSE(ps.parse_row("5\t6"));
}

TEST(Parser, ParserInt) {
	parser::Parser ps;
    EXPECT_TRUE(ps.set_format("int"));
	EXPECT_TRUE(ps.parse_row("5"));

    std::vector<int*> value = ps.get_column<int>(0);
	EXPECT_EQ(5, *value[0]);
    EXPECT_EQ(1, value.size());
}

TEST(Parser, ParserIntArray) {
	parser::Parser ps;
    EXPECT_TRUE(ps.set_format("int"));
	EXPECT_TRUE(ps.parse_row("2:5,6"));

    std::vector<int*> value = ps.get_column<int>(0);
	EXPECT_EQ(5, *value[0]);
	EXPECT_EQ(6, *value[1]);
	EXPECT_EQ(2, value.size());
}

TEST(Parser, ParserFloat) {
	parser::Parser ps;
    EXPECT_TRUE(ps.set_format("float"));
	EXPECT_TRUE(ps.parse_row("3.1415"));

    std::vector<float*> value = ps.get_column<float>(0);
	EXPECT_LE(fabs(3.1415 - *value[0]), 1e-5);
    EXPECT_EQ(1, value.size());
}

TEST(Parser, ParserFloatArray) {
	parser::Parser ps;
    EXPECT_TRUE(ps.set_format("float"));
	EXPECT_TRUE(ps.parse_row("2:3.1415,2.7182"));

    std::vector<float*> value = ps.get_column<float>(0);
	EXPECT_LE(fabs(3.1415 - *value[0]), 1e-5);
	EXPECT_LE(fabs(2.7182 - *value[1]), 1e-5);
	EXPECT_EQ(2, value.size());
}

TEST(Parser, ParserChar) {
    std::string name = "Sheldon";
	parser::Parser ps;
    EXPECT_TRUE(ps.set_format("char"));
	EXPECT_TRUE(ps.parse_row(name));

    std::vector<char*> value = ps.get_column<char>(0);
    EXPECT_EQ(name.compare(value[0]), 0);
    EXPECT_EQ(1, value.size());
}

TEST(Parser, ParserCharArray) {
	parser::Parser ps;
    std::string name1 = "Shelton";
    std::string name2 = "Cherry";
    EXPECT_TRUE(ps.set_format("char"));
	EXPECT_TRUE(ps.parse_row("2:Shelton,Cherry"));

    std::vector<char*> value = ps.get_column<char>(0);
    EXPECT_EQ(name1.compare(value[0]), 0);
    EXPECT_EQ(name2.compare(value[1]), 0);
    EXPECT_EQ(2, value.size());
}

TEST(Parser, ParserUser) {
	parser::Parser ps;
    std::string name = "Joe";
    EXPECT_TRUE(ps.set_format("User"));
	EXPECT_TRUE(ps.parse_row("0 Joe 15 40.5"));

    std::vector<utils::User*> user = ps.get_column<utils::User>(0);
    EXPECT_EQ(0, user[0]->id);
    EXPECT_EQ(name.compare(user[0]->name.get()), 0);
    EXPECT_EQ(15, user[0]->age);
	EXPECT_LE(fabs(40.5 - user[0]->weight), 1e-5);
    EXPECT_EQ(1, user.size());
}

TEST(Parser, ParserUserMissValue) {
	parser::Parser ps;
    EXPECT_TRUE(ps.set_format("User"));
    EXPECT_TRUE(ps.parse_row("Joe 15 40.5"));

    std::vector<utils::User*> user = ps.get_column<utils::User>(0);
    EXPECT_EQ(nullptr, user[0]);
}

TEST(Parser, ParserUserArray) {
	parser::Parser ps;
    std::string name1 = "Joe";
    std::string name2 = "Lucy";
    EXPECT_TRUE(ps.set_format("User"));
	EXPECT_TRUE(ps.parse_row("2:0 Joe 15 40.5, 1 Lucy 29 50.4"));

    std::vector<utils::User*> user = ps.get_column<utils::User>(0);
    EXPECT_EQ(0, user[0]->id);
    EXPECT_EQ(name1.compare(user[0]->name.get()), 0);
    EXPECT_EQ(15, user[0]->age);
	EXPECT_LE(fabs(40.5 - user[0]->weight), 1e-5);
    EXPECT_EQ(1, user[1]->id);
    EXPECT_EQ(name2.compare(user[1]->name.get()), 0);
    EXPECT_EQ(29, user[1]->age);
	EXPECT_LE(fabs(50.4 - user[1]->weight), 1e-5);
    EXPECT_EQ(2, user.size());
}

TEST(Parser, ParserCharacterInDigits) {
	parser::Parser ps;
    EXPECT_TRUE(ps.set_format("int\tfloat\tdouble"));
	EXPECT_TRUE(ps.parse_row("5a\t2.3b\t3.14b"));

    std::vector<int*> v_int = ps.get_column<int>(0);
	EXPECT_EQ(nullptr, v_int[0]);
    std::vector<float*> v_float = ps.get_column<float>(1);
	EXPECT_EQ(nullptr, v_float[0]);
    std::vector<double*> v_double = ps.get_column<double>(2);
	EXPECT_EQ(nullptr, v_double[0]);
}

TEST(Parser, ParserEmptyString) {
	parser::Parser ps;
    EXPECT_TRUE(ps.set_format("int\tfloat\tdouble\tchar\tUser"));
	EXPECT_TRUE(ps.parse_row(" \t \t \t \t"));

    std::vector<int*> v_int = ps.get_column<int>(0);
	EXPECT_EQ(nullptr, v_int[0]);
    std::vector<float*> v_float = ps.get_column<float>(1);
	EXPECT_EQ(nullptr, v_float[0]);
    std::vector<double*> v_double = ps.get_column<double>(2);
	EXPECT_EQ(nullptr, v_double[0]);
    std::vector<char*> v_char = ps.get_column<char>(3);
    EXPECT_EQ(' ', *v_char[0]);
    std::vector<utils::User*> v_user = ps.get_column<utils::User>(4);
    EXPECT_EQ(nullptr, v_user[0]);
}

TEST(Parser, ParserLine) {
	parser::Parser ps;
    EXPECT_TRUE(ps.set_format("User\tfloat\tint\tchar\tdouble"));
	EXPECT_TRUE(ps.parse_row("2 Wang 28 63.5\t2.718\t2:40,6\tChina\t1.52849"));

    std::vector<utils::User*> user = ps.get_column<utils::User>(0);
    EXPECT_EQ(2, user[0]->id);
    std::string name = "Wang";
    EXPECT_EQ(name.compare(user[0]->name.get()), 0);
    EXPECT_EQ(28, user[0]->age);
    EXPECT_LE(fabs(63.5 - user[0]->weight), 1e-5);
    EXPECT_EQ(1, user.size());

    std::vector<float*> v_float = ps.get_column<float>(1);
	EXPECT_LE(fabs(2.718 - *v_float[0]), 1e-5);
    EXPECT_EQ(1, v_float.size());

    std::vector<int*> v_int = ps.get_column<int>(2);
	EXPECT_EQ(40, *v_int[0]);
	EXPECT_EQ(6, *v_int[1]);
	EXPECT_EQ(2, v_int.size());

    std::vector<char*> v_char = ps.get_column<char>(3);
    std::string add = "China";
    EXPECT_EQ(add.compare(v_char[0]), 0);
    EXPECT_EQ(1, v_char.size());

    std::vector<double*> v_double = ps.get_column<double>(4);
    EXPECT_LE(fabs(1.52849 - *v_double[0]), 1e-8);
    EXPECT_EQ(1, v_double.size());
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
