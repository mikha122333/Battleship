#include "pch.h"

#include "Ship.h"
//#define SHIP_TESTS
#ifdef SHIP_TESTS
TEST(te_sh,constructor_1) {
	Position p(5, 5);
	Ship s(3, p, Horizontal);
	EXPECT_EQ(s.row(), 5);
	EXPECT_EQ(s.col(), 5);
	EXPECT_EQ(s.size(), 3);
	EXPECT_EQ(s.direction(), Horizontal);
}
TEST(te_sh, constructor_1_error) {
	Position p(5, 5);
	EXPECT_ANY_THROW(Ship s(2323, p, Horizontal));
}
TEST(te_sh, constructor_2) {
	Ship s(3,'h',5,'e');
	EXPECT_EQ(s.row(), 5);
	EXPECT_EQ(s.col(), 5);
	EXPECT_EQ(s.size(), 3);
	EXPECT_EQ(s.direction(), Horizontal);
}
TEST(te_sh, constructor_2_error_1) {
	EXPECT_ANY_THROW(Ship s(-1, 'h', 5, 'e'));
}
TEST(te_sh, constructor_2_error_2) {
	EXPECT_ANY_THROW(Ship s(3, 'l', 5, 'e'));
}
TEST(te_sh, constructor_2_error_3) {
	EXPECT_ANY_THROW(Ship s(3, 'h', 11, 'e'));
}
TEST(te_sh, constructor_3) {
	Ship s("3 h 5e");
	EXPECT_EQ(s.row(), 5);
	EXPECT_EQ(s.col(), 5);
	EXPECT_EQ(s.size(), 3);
	EXPECT_EQ(s.direction(), Horizontal);
}
TEST(te_sh, constructor_3_error_1) {
	EXPECT_ANY_THROW(Ship s("5 h 5e"));
}
TEST(te_sh, constructor_3_error_2) {
	EXPECT_ANY_THROW(Ship s("3 k 5e"));
}
TEST(te_sh, constructor_3_error_3) {
	EXPECT_ANY_THROW(Ship s("3 h 5p"));
}
TEST(te_sh, setter_1) {
	Position p(5, 5);
	Ship s(1, p, Horizontal);
	s.col(6);
	EXPECT_EQ(s.col(), 6);
}
TEST(te_sh, setter_2) {
	Position p(5, 5);
	Ship s(1, p, Horizontal);
	s.row(6);
	EXPECT_EQ(s.row(), 6);
}
TEST(te_sh, setter_3) {
	Position p(5, 5);
	Ship s(1, p, Horizontal);
	s.direction(Vertical);
	EXPECT_EQ(s.direction(), Vertical);
}
TEST(te_sh, setter_4) {
	Position p(5, 5);
	Ship s(1, p, Horizontal);
	s.direction('v');
	EXPECT_EQ(s.direction(), Vertical);
}
TEST(te_sh, setter_5) {
	Position p(5, 5);
	Ship s(1, p, Horizontal);
	s.size(3);
	EXPECT_EQ(s.size(), 3);
}
TEST(te_sh, setter_6) {
	Position p2(4, 4);
	Ship s(1, p2, Horizontal);
	Position p(5, 5);
	s.position(p);
	EXPECT_EQ(s.col(), 5);
	EXPECT_EQ(s.row(), 5);
}
TEST(te_sh, setter_7) {
	Position p(5, 5);
	Ship s(1, p, Horizontal);
	s.col('f');
	EXPECT_EQ(s.col(), 6);
}
TEST(te_sh, setter_1_err) {
	Position p(5, 5);
	Ship s(1, p, Horizontal);
	EXPECT_ANY_THROW(s.col(20));
}
TEST(te_sh, setter_2_err) {
	Position p(5, 5);
	Ship s(1, p, Horizontal);
	EXPECT_ANY_THROW(s.row(20));
}
TEST(te_sh, setter_3_err) {
	Position p(10, 5);
	Ship s(2, p, Horizontal);
	EXPECT_ANY_THROW(s.direction(Vertical));
}
TEST(te_sh, setter_4_err) {
	Position p(10, 5);
	Ship s(2, p, Horizontal);
	EXPECT_ANY_THROW(s.direction('v'));
}
TEST(te_sh, setter_5_err) {
	Position p(5, 5);
	Ship s(1, p, Horizontal);
	EXPECT_ANY_THROW(s.size(20));
}
TEST(te_sh, setter_6_err) {
	Position p2(4, 4);
	Ship s(2, p2, Horizontal);
	Position p(10, 10);
	EXPECT_ANY_THROW(s.position(p));
}
TEST(te_sh, setter_7_err) {
	Position p(5, 5);
	Ship s(1, p, Horizontal);
	EXPECT_ANY_THROW(s.col(';'));
}
#endif
