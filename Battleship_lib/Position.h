#pragma once
#include <cstdlib>
#include <ctime>
#include<string>
#include<stdexcept>
#include<sstream>
#include <cctype>
class Position {
private:
    int _row;
    int _col;
    static const int _max_row;
    static const int _max_col;
public:
    Position();
    Position(const int&, const int&);
    Position(const int&, const char&);
    Position(const Position&);
    Position(const std::string&);
    inline int row()const noexcept { return _row; }
    inline int col()const noexcept { return _col; }
    inline char char_col()const noexcept { return 'A' + _col - 1; }
    void row(const int&);
    void col(const int&);
    void col(const char&);
    friend void parse(const std::string&, Position&);
    friend bool is_collision(const int&);
    friend bool is_collision(const char&);
};