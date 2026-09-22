#include "Position.h"
const int Position::_max_row = 10;
const int Position::_max_col = 10;
Position::Position() {
    _row = 1;
    _col = 1;
}
Position::Position(const int& row, const int& col) {
    if (is_good_col(col)&&is_good_row(row)) {
        _col = col;
        _row = row;
    }
    else {
        throw std::logic_error("Invalid input: incorrect position");
    }
}
Position::Position(const Position& p1) {
    this->_col = p1._col;
    this->_row = p1._row;
}
Position parse(const std::string& str) {
    int r, c;
    char ch;
    std::istringstream iss(str);
    iss >> ch >> r >> ch >> c >> ch;
    return Position(r, c);
}
Position::Position(const std::string& s1) {
    Position p = parse(s1);
    _row = p._row;
    _col = p._col;
}
void Position::row(const int& row) {
    if (is_good_row(row)) {
        _row = row;
    }
    else {
        throw std::logic_error("Invalid input: incorrect position");
    }
}
void Position::col(const int& col) {
    if (is_good_col(col)) {
        _col = col;
    }
    else {
        throw std::logic_error("Invalid input: incorrect position");
    }
}
std::string  to_string(const Position& p1)noexcept {
    std::string res = "(" + std::to_string(p1._row) + ", " + std::to_string(p1._col) + ")";
    return res;
}