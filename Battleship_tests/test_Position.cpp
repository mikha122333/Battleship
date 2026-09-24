#include "pch.h"

#include "Position.h"
//#define POSITION_TESTS
#ifdef POSITION_TESTS
TEST(te_po,constructor_1) {
	Position p(2, 3);
	EXPECT_EQ(p.row(), 2);
	EXPECT_EQ(p.col(), 3);
}
TEST(te_po, constructor_1_exception) {
	EXPECT_ANY_THROW(Position(11, 0));
}
TEST(te_po, constructor_2) {
	Position p(2, 'A');
	EXPECT_EQ(p.row(), 2);
	EXPECT_EQ(p.col(), 1);
	EXPECT_EQ(p.char_col(), 'A');
}
TEST(te_po, constructor_2_exception) {
	EXPECT_ANY_THROW(Position(3, '/'));
}
TEST(te_po, constructor_copy) {
	Position p2(2, 'A');
	Position p(p2);
	EXPECT_EQ(p.row(), 2);
	EXPECT_EQ(p.col(), 1);
	EXPECT_EQ(p.char_col(), 'A');
}
TEST(te_op, setter_row) {
	Position p(1,1);
	p.row(3);
	EXPECT_EQ(p.row(), 3);
}
TEST(te_op, setter_row_error) {
	Position p(1, 1);
	EXPECT_ANY_THROW(p.row(55));
}
TEST(te_op, setter_col_num) {
	Position p(1, 1);
	p.col(3);
	EXPECT_EQ(p.col(), 3);
}
TEST(te_op, setter_col_char) {
	Position p(1, 1);
	p.col('b');
	EXPECT_EQ(p.char_col(), 'B');
}
TEST(te_op, setter_col_num_error) {
	Position p(1, 1);
	EXPECT_ANY_THROW( p.col(20));
}
TEST(te_op, setter_col_char_error) {
	Position p(1, 1);
	EXPECT_ANY_THROW(p.col('['));
}
#endif