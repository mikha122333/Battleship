#include "pch.h"
#include "Game.h"
#include <sstream>

#define GAME_TESTS
#ifdef GAME_TESTS

// ---------- Конструктор ----------

TEST(te_game, constructor) {
    Game g;
    SUCCEED();
}

// ---------- Ошибки на этапе расстановки ----------

TEST(te_game, start_empty_line_during_placement_throws) {
    Game g;
    std::istringstream iss("\n");
    std::streambuf* old_buf = std::cin.rdbuf(iss.rdbuf());
    testing::internal::CaptureStdout();
    EXPECT_ANY_THROW(g.start());
    testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_buf);
    std::cin.clear();
}

TEST(te_game, start_invalid_ship_string_throws) {
    Game g;
    std::istringstream iss("bad string\n");
    std::streambuf* old_buf = std::cin.rdbuf(iss.rdbuf());
    testing::internal::CaptureStdout();
    EXPECT_ANY_THROW(g.start());
    testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_buf);
    std::cin.clear();
}

TEST(te_game, start_too_large_ship_throws) {
    Game g;
    std::istringstream iss("5 h 1a\n");   // размер 5 недопустим
    std::streambuf* old_buf = std::cin.rdbuf(iss.rdbuf());
    testing::internal::CaptureStdout();
    EXPECT_ANY_THROW(g.start());
    testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_buf);
    std::cin.clear();
}

TEST(te_game, start_ship_collision_throws) {
    Game g;
    std::istringstream iss("1 h 5e\n1 h 5e\n");  // второй пересекается с первым
    std::streambuf* old_buf = std::cin.rdbuf(iss.rdbuf());
    testing::internal::CaptureStdout();
    EXPECT_ANY_THROW(g.start());
    testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_buf);
    std::cin.clear();
}

// ---------- Промежуточный вывод ----------

TEST(te_game, start_prints_ships_left) {
    Game g;
    std::istringstream iss("\n");
    std::streambuf* old_buf = std::cin.rdbuf(iss.rdbuf());
    testing::internal::CaptureStdout();
    try { g.start(); }
    catch (...) {}
    std::string out = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_buf);
    std::cin.clear();
    EXPECT_NE(out.find("Ships Left"), std::string::npos);
}

// ---------- Полная расстановка + некорректный ход ----------

TEST(te_game, start_full_setup_then_invalid_move_throws) {
    Game g;
    std::istringstream iss(
        "1 h 1a\n"
        "2 h 4a\n"
        "\n"
        "1 h 1a\n"
        "2 h 4a\n"
        "\n"
        "0 A\n"
    );
    std::streambuf* old_buf = std::cin.rdbuf(iss.rdbuf());
    testing::internal::CaptureStdout();
    EXPECT_ANY_THROW(g.start());
    testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_buf);
    std::cin.clear();
}

// ---------- Полная расстановка + один валидный ход ----------

TEST(te_game, start_full_setup_one_valid_move) {
    Game g;
    std::istringstream iss(
        "1 h 1a\n"
        "2 h 4a\n"
        "\n"
        "1 h 1a\n"
        "2 h 4a\n"
        "\n"
        "5 E\n"
        "0 A\n"
    );
    std::streambuf* old_buf = std::cin.rdbuf(iss.rdbuf());
    testing::internal::CaptureStdout();
    EXPECT_ANY_THROW(g.start());
    std::string out = testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_buf);
    std::cin.clear();
    EXPECT_NE(out.find("COMPUTER GAME FIELD"), std::string::npos);
    EXPECT_NE(out.find("YOUR PLAY FIELD"), std::string::npos);
}

// ---------- Компьютер успевает сделать ход ----------

TEST(te_game, start_computer_gets_to_move) {
    Game g;
    std::istringstream iss(
        "1 h 1a\n"
        "2 h 4a\n"
        "\n"
        "1 h 1a\n"
        "2 h 4a\n"
        "\n"
        "10 A\n"
        "9 A\n"
        "8 A\n"
        "0 A\n"
    );
    std::streambuf* old_buf = std::cin.rdbuf(iss.rdbuf());
    testing::internal::CaptureStdout();
    EXPECT_ANY_THROW(g.start());
    testing::internal::GetCapturedStdout();
    std::cin.rdbuf(old_buf);
    std::cin.clear();
}

#endif