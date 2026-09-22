#include "Position.h"
const int Position::_max_row = 10;
const int Position::_max_col = 10;
bool is_collision(const int& row) {
        return (row > 0 && row <= Position::_max_row);
}
bool is_collision(const char& col) {
        return ((col >= 'A' && col < Position::_max_col + 'A')|| (col >= 'a' && col < Position::_max_col + 'a'));
}
Position::Position() {
    std::srand(std::time(nullptr));
    _row = (std::rand() % _max_row) + 1;
    _col = (std::rand() % _max_col) + 1;
}
Position::Position(const int& row, const int& col) {
    if (!is_collision(row) || !is_collision(col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = row;
    _col = col;
}
Position::Position(const int& row, const char& col) {
    if (!is_collision(row) || !is_collision(col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = row;
    if(std::isupper(col))
        _col = int(col - 'A' + 1);
    else
        _col = int(col - 'a' + 1);
}
Position::Position(const Position& p1) {
    _col = p1._col;
    _row = p1._row;
}
Position::Position(const std::string& s1) {
    parse(s1, *this);
}
void Position::row(const int& row) {
    if (!is_collision(row)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = row;
}
void parse(const std::string& s1, Position& p1) {
    int row;
    char col2;
    int tmp;
    if (s1[1] == '0')
        tmp = 2;
    else tmp = 1;
    std::istringstream iss(s1.substr(0, tmp));
    std::istringstream iss2(s1.substr(tmp, s1.size() - 1));
    iss >> row;
    iss2 >> col2;
    p1.row(row);
    p1.col(col2);
}
void Position::col(const int& col) {
    if (!is_collision(char(col+'A'-1))) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _col = col;
}
void Position::col(const char& col) {
    if (!is_collision(col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    if(std::isupper(col))
        _col = int(col - 'A' + 1);
    else
        _col = int(col - 'a' + 1);
}
