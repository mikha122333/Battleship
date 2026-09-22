#include "pch.h"
#include "Player.h"

//#define PLAYER_TESTS
#ifdef PLAYER_TESTS

TEST(te_pl, constructor_default_counts_zero) {
    Player p;
    EXPECT_FALSE(p.check_ready());
    EXPECT_TRUE(p.check_lose());
}
TEST(te_pl, set_ship_one_boat) {
    Player p;
    Ship s(1, 'h', 5, 'e');
    EXPECT_NO_THROW(p.set_ship(s));
    EXPECT_FALSE(p.check_ready());
    EXPECT_FALSE(p.check_lose());
}

TEST(te_pl, set_ship_ok_all_types) {
    Player p;
    EXPECT_NO_THROW(p.set_ship(Ship(4, 'h', 1, 'a')));
    EXPECT_NO_THROW(p.set_ship(Ship(3, 'h', 3, 'a')));
    EXPECT_NO_THROW(p.set_ship(Ship(2, 'h', 5, 'a')));  
    EXPECT_NO_THROW(p.set_ship(Ship(1, 'h', 7, 'a')));  
}

TEST(te_pl, set_ship_too_many_boats_throws) {
    Player p;
    EXPECT_NO_THROW(p.set_ship(Ship(1, 'h', 1, 'a')));
    EXPECT_NO_THROW(p.set_ship(Ship(1, 'h', 1, 'c')));
    EXPECT_NO_THROW(p.set_ship(Ship(1, 'h', 1, 'e')));
    EXPECT_NO_THROW(p.set_ship(Ship(1, 'h', 1, 'g')));
    EXPECT_ANY_THROW(p.set_ship(Ship(1, 'h', 1, 'i')));
}

TEST(te_pl, set_ship_too_many_destroyers_throws) {
    Player p;
    EXPECT_NO_THROW(p.set_ship(Ship(2, 'h', 1, 'a')));
    EXPECT_NO_THROW(p.set_ship(Ship(2, 'h', 3, 'a')));
    EXPECT_NO_THROW(p.set_ship(Ship(2, 'h', 5, 'a')));
    EXPECT_ANY_THROW(p.set_ship(Ship(2, 'h', 7, 'a')));
}

TEST(te_pl, set_ship_too_many_cruisers_throws) {
    Player p;
    EXPECT_NO_THROW(p.set_ship(Ship(3, 'h', 1, 'a')));
    EXPECT_NO_THROW(p.set_ship(Ship(3, 'h', 3, 'a')));
    EXPECT_ANY_THROW(p.set_ship(Ship(3, 'h', 5, 'a')));
}

TEST(te_pl, set_ship_too_many_battleships_throws) {
    Player p;
    EXPECT_NO_THROW(p.set_ship(Ship(4, 'h', 1, 'a')));
    EXPECT_ANY_THROW(p.set_ship(Ship(4, 'h', 6, 'a')));
}

TEST(te_pl, set_ship_collision_throws) {
    Player p;
    p.set_ship(Ship(1, 'h', 5, 'e'));
    EXPECT_ANY_THROW(p.set_ship(Ship(1, 'h', 5, 'e')));
}

TEST(te_pl, set_ship_adjacent_throws) {
    Player p;
    p.set_ship(Ship(1, 'h', 5, 'e'));
    EXPECT_ANY_THROW(p.set_ship(Ship(1, 'h', 5, 'f')));
    EXPECT_ANY_THROW(p.set_ship(Ship(1, 'h', 4, 'f')));
    EXPECT_ANY_THROW(p.set_ship(Ship(1, 'h', 6, 'f')));
}
TEST(te_pl, check_ready_true_after_all_ships) {
    Player p;
    p.set_ship(Ship(4, 'h', 1, 'a'));
    p.set_ship(Ship(3, 'h', 3, 'a'));
    p.set_ship(Ship(3, 'h', 5, 'a'));
    p.set_ship(Ship(2, 'h', 7, 'a'));
    p.set_ship(Ship(2, 'h', 9, 'a'));
    p.set_ship(Ship(2, 'h', 1, 'f'));
    p.set_ship(Ship(1, 'h', 3, 'f'));
    p.set_ship(Ship(1, 'h', 3, 'h'));
    p.set_ship(Ship(1, 'h', 5, 'f'));
    p.set_ship(Ship(1, 'h', 5, 'h'));

    EXPECT_TRUE(p.check_ready());
    EXPECT_FALSE(p.check_lose());
}
TEST(te_pl, check_ready_false_without_all_ships) {
    Player p;
    p.set_ship(Ship(4, 'h', 1, 'a'));
    EXPECT_FALSE(p.check_ready());
}
TEST(te_pl, set_action_miss) {
    Player p;
    EXPECT_EQ(p.set_action(1, 'A'), Missed);
}

TEST(te_pl, set_action_hit_boat) {
    Player p;
    p.set_ship(Ship(1, 'h', 5, 'e'));
    EXPECT_EQ(p.set_action(5, 'E'), BoatDestroyed);
}

TEST(te_pl, set_action_hit_destroyer_decrements_count) {
    Player p;
    p.set_ship(Ship(2, 'h', 5, 'e'));
    EXPECT_FALSE(p.check_lose());
    EXPECT_EQ(p.set_action(5, 'E'), Hit);
    EXPECT_EQ(p.set_action(5, 'F'), DestroyersDestroyed);
    EXPECT_TRUE(p.check_lose());
}

TEST(te_pl, set_action_hit_cruiser_decrements_count) {
    Player p;
    p.set_ship(Ship(3, 'h', 5, 'e'));
    p.set_action(5, 'E');
    p.set_action(5, 'F');
    EXPECT_EQ(p.set_action(5, 'G'), CruisersDestroyed);
    EXPECT_TRUE(p.check_lose());
}

TEST(te_pl, set_action_hit_battleship_decrements_count) {
    Player p;
    p.set_ship(Ship(4, 'h', 5, 'e'));
    p.set_action(5, 'E');
    p.set_action(5, 'F');
    p.set_action(5, 'G');
    EXPECT_EQ(p.set_action(5, 'H'), BattleshipDestroyed);
    EXPECT_TRUE(p.check_lose());
}

TEST(te_pl, set_action_invalid_throws) {
    Player p;
    EXPECT_ANY_THROW(p.set_action(0, 'A'));
    EXPECT_ANY_THROW(p.set_action(11, 'A'));
    EXPECT_ANY_THROW(p.set_action(5, '@'));
    EXPECT_ANY_THROW(p.set_action(5, 'K'));
}
TEST(te_pl, check_lose_false_with_alive_ship) {
    Player p;
    p.set_ship(Ship(2, 'h', 5, 'e'));
    EXPECT_FALSE(p.check_lose());
    p.set_action(5, 'E');
    EXPECT_FALSE(p.check_lose());
}

TEST(te_pl, check_lose_true_after_all_destroyed) {
    Player p;
    p.set_ship(Ship(1, 'h', 5, 'e'));
    p.set_action(5, 'E');
    EXPECT_TRUE(p.check_lose());
}

TEST(te_pl, check_lose_true_initially) {
    Player p;
    EXPECT_TRUE(p.check_lose());
}

#endif