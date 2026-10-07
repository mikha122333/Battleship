#include "Position.h"
const int Position::_max_row = 10;
const int Position::_max_col = 10;
bool is_collision(int row) {
        return (row > 0 && row <= Position::_max_row);
}
bool is_collision(char col) {
    return (std::toupper(col) >= 'A' && std::toupper(col) < Position::_max_col + 'A');
}
Position::Position() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> rand_for_row(0, _max_row);
    std::uniform_int_distribution<int> rand_for_col(0, _max_col);
    _row = rand_for_row(gen);
    _col = rand_for_row(gen);
}
Position::Position(const int row, const int col) {
    if (!is_collision(row) || !is_collision(col)) {
        throw std::logic_error("Invalid input: incorrect position");
    }
    _row = row;
    _col = col;
}
Position::Position(const int row, const char col) {
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
void parse(const std::string& s1, Position& p1) {
    int row;
    char col2;
    int tmp;
    if (s1[1] >= '0'&& s1[1]<=9)
        tmp = 2;
    else tmp = 1;
    std::istringstream iss(s1.substr(0, tmp));
    std::istringstream iss2(s1.substr(tmp, s1.size() - 1));
    if (!(iss >> row && iss2 >> col2))
        throw std::logic_error("wrong input");
    p1.row(row);
    p1.col(col2);
}
