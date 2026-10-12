#pragma once
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdexcept>
#include <sstream>
#include<iostream>
#include <cctype>
#include<iomanip>
#include<random>
bool is_collision(char);
bool is_collision(int);
class Position {
private:
    int _row;
    int _col;
    static const int _max_row;
    static const int _max_col;
public:
    Position();
    Position(const int, const int);
    Position(const int, const char);
    Position(const Position&);
    Position(const std::string&);
    inline int row()const noexcept { return _row; }
    inline int col()const noexcept { return _col; }
    inline char char_col()const noexcept { return 'A' + _col - 1; }
    friend bool is_collision(int);
    friend bool is_collision(char);
    inline void row(const int& row){
        if (!is_collision(row)) {
            throw std::logic_error("Invalid input: incorrect position");
        }
        _row = row;
    }
    inline void col(const int& col) {
        if (!is_collision(char(col + 'A' - 1))) {
            throw std::logic_error("Invalid input: incorrect position");
        }
        _col = col;
    }
    inline void col(const char& col) {
        if (!is_collision(col)) {
            throw std::logic_error("Invalid input: incorrect position");
        }
        _col = int(toupper(col) - 'A' + 1);
    }
    friend void parse(const std::string&, Position&);
};