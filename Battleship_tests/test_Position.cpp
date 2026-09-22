#include "pch.h"

#include "Position.h"
TEST(t_p_num,test_is_pos_corrrect) {
	Position p(2, 3);
	EXPECT_TRUE(p.col(), 3);
	EXPECT_TRUE(p.row(), 2);
}
TEST(t_p_num, test_is_pos_corrrect_without_data) {
	Position p;
	EXPECT_TRUE(p.col(), 1);
	EXPECT_TRUE(p.row(), 1);
}
TEST(t_p_num, error_if_higher_10) {
	EXPECT_ANY_THROW(Position(1, 11));
}
TEST(t_p_str, test_is_pos_corrrect) {
	Position p("(2 , 3)");
	EXPECT_TRUE(p.col(), 3);
	EXPECT_TRUE(p.row(), 2);
}
TEST(t_p_str, error_if_higher_10) {
	EXPECT_ANY_THROW(Position("(1 , 11)"));
}
TEST(t_p_num, error_if_lower_1) {
	EXPECT_ANY_THROW(Position(1, 0));
}
TEST(t_p_num, is_setter_work) {
	Position p;
	p.col(5);
	p.row(3);
	EXPECT_TRUE(p.col(), 5);
	EXPECT_TRUE(p.row(), 3);
}
TEST(t_p_num, is_setter_can_do_error) {
	Position p;
	EXPECT_ANY_THROW(p.col(11));
}