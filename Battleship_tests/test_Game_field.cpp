#include "pch.h"
#include "Game_field.h"

//#define GAME_FIELD_TESTS
#ifdef GAME_FIELD_TESTS
static int count_char(const std::string& str, char ch) {
    int cnt = 0;
    for (char c : str) {
        if (c == ch) ++cnt;
    }
    return cnt;
}
TEST(te_gf, constructor_default) {
    Game_field f;
    std::string s = to_string(f);
    EXPECT_NE(s.find("  | A B C D E F G H I J|"), std::string::npos);
    EXPECT_NE(s.find("1 |"), std::string::npos);
    EXPECT_NE(s.find("10|"), std::string::npos);
    EXPECT_EQ(s.find('X'), std::string::npos);
    EXPECT_EQ(s.find('*'), std::string::npos);
}

TEST(te_gf, to_string_show_ships) {
    Game_field f;
    Ship s(2, 'h', 3, 'c');
    f.set(s);
    std::string show = to_string(f, true);
    std::string hide = to_string(f, false);
    EXPECT_NE(show.find('*'), std::string::npos);
    EXPECT_EQ(hide.find('*'), std::string::npos);
    EXPECT_EQ(count_char(show, '*'), 2);
}
TEST(te_gf, set_ship_horizontal_show) {
    Game_field f;
    Ship s(3, 'h', 5, 'e'); 
    f.set(s);
    std::string show = to_string(f, true);
    EXPECT_EQ(count_char(show, '*'), 3);
}

TEST(te_gf, set_ship_vertical_show) {
    Game_field f;
    Ship s(2, 'v', 5, 'e'); 
    f.set(s);
    std::string show = to_string(f, true);
    EXPECT_EQ(count_char(show, '*'), 2);
}

TEST(te_gf, set_ship_hide) {
    Game_field f;
    Ship s(1, 'h', 5, 'e');
    f.set(s);
    std::string hide = to_string(f, false);
    EXPECT_EQ(hide.find('*'), std::string::npos);
    EXPECT_EQ(hide.find('X'), std::string::npos);
}

TEST(te_gf, set_ship_collision_overlap_throws) {
    Game_field f;
    Ship s1(1, 'h', 5, 'e');
    f.set(s1);
    Ship s2(1, 'h', 5, 'e');
    EXPECT_ANY_THROW(f.set(s2));
}

TEST(te_gf, set_ship_collision_adjacent_throws) {
    Game_field f;
    Ship s1(1, 'h', 5, 'e');
    f.set(s1);
    Ship s2(1, 'h', 5, 'f'); 
    EXPECT_ANY_THROW(f.set(s2));
    Ship s3(1, 'h', 5, 'd'); 
    EXPECT_ANY_THROW(f.set(s3));
    Ship s4(1, 'h', 4, 'e'); 
    EXPECT_ANY_THROW(f.set(s4));
    Ship s5(1, 'h', 6, 'e'); 
    EXPECT_ANY_THROW(f.set(s5));
    Ship s6(1, 'h', 4, 'f'); 
    EXPECT_ANY_THROW(f.set(s6));
}

TEST(te_gf, is_collision_empty_field_true) {
    Game_field f;
    Ship s(4, 'h', 1, 'a');
    EXPECT_TRUE(is_collision(f, s));
}

TEST(te_gf, is_collision_overlap_false) {
    Game_field f;
    Ship s1(2, 'h', 5, 'e');
    f.set(s1);
    Ship s2(1, 'h', 5, 'e');
    EXPECT_FALSE(is_collision(f, s2));
}

TEST(te_gf, is_collision_adjacent_false) {
    Game_field f;
    Ship s1(1, 'h', 5, 'e');
    f.set(s1);
    Ship s2(1, 'h', 5, 'f');
    EXPECT_FALSE(is_collision(f, s2));
    Ship s3(1, 'h', 4, 'e');
    EXPECT_FALSE(is_collision(f, s3));
    Ship s4(1, 'h', 4, 'f');
    EXPECT_FALSE(is_collision(f, s4));
}

TEST(te_gf, is_collision_boundary_true) {
    Game_field f;
    Ship s1(1, 'h', 1, 'a');  
    EXPECT_TRUE(is_collision(f, s1));
    Ship s2(1, 'h', 10, 'j');  
    EXPECT_TRUE(is_collision(f, s2));
    Ship s3(4, 'h', 1, 'a');   
    EXPECT_TRUE(is_collision(f, s3));
    Ship s4(4, 'v', 7, 'j');  
    EXPECT_TRUE(is_collision(f, s4));
}


TEST(te_gf, set_move_miss) {
    Game_field f;
    EXPECT_EQ(f.set(1, 'A'), Missed);
    EXPECT_EQ(f.set(10, 'J'), Missed);
}

TEST(te_gf, set_move_invalid_row_throws) {
    Game_field f;
    EXPECT_ANY_THROW(f.set(0, 'A'));
    EXPECT_ANY_THROW(f.set(11, 'A'));
}

TEST(te_gf, set_move_invalid_col_throws) {
    Game_field f;
    EXPECT_ANY_THROW(f.set(1, '@')); 
    EXPECT_ANY_THROW(f.set(1, 'K')); 
}

TEST(te_gf, set_move_hit_boat_destroyed) {
    Game_field f;
    Ship s(1, 'h', 5, 'e');
    f.set(s);
    EXPECT_EQ(f.set(5, 'E'), BoatDestroyed);
}

TEST(te_gf, set_move_hit_destroyer_destroyed) {
    Game_field f;
    Ship s(2, 'h', 5, 'e'); 
    f.set(s);
    EXPECT_EQ(f.set(5, 'E'), Hit);
    EXPECT_EQ(f.set(5, 'F'), DestroyersDestroyed);
}

TEST(te_gf, set_move_hit_cruiser_destroyed) {
    Game_field f;
    Ship s(3, 'h', 5, 'e'); 
    f.set(s);
    EXPECT_EQ(f.set(5, 'E'), Hit);
    EXPECT_EQ(f.set(5, 'F'), Hit);
    EXPECT_EQ(f.set(5, 'G'), CruisersDestroyed);
}

TEST(te_gf, set_move_hit_battleship_destroyed) {
    Game_field f;
    Ship s(4, 'h', 5, 'e'); 
    f.set(s);
    EXPECT_EQ(f.set(5, 'E'), Hit);
    EXPECT_EQ(f.set(5, 'F'), Hit);
    EXPECT_EQ(f.set(5, 'G'), Hit);
    EXPECT_EQ(f.set(5, 'H'), BattleshipDestroyed);
}

TEST(te_gf, set_move_hit_vertical_destroyer) {
    Game_field f;
    Ship s(2, 'v', 5, 'e'); 
    f.set(s);
    EXPECT_EQ(f.set(5, 'E'), Hit);
    EXPECT_EQ(f.set(6, 'E'), DestroyersDestroyed);
}

TEST(te_gf, set_move_marks_hit) {
    Game_field f;
    Ship s(1, 'h', 3, 'c');
    f.set(s);
    f.set(3, 'C');
    std::string show = to_string(f, true);
    EXPECT_NE(show.find('X'), std::string::npos);
}

#endif