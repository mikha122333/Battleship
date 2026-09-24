#include "Ship.h"

bool is_collision(const int size, const Position& pos, const Direction dir) noexcept {
    if (size < 1 || size > 4) return false;
    int col_plus = 0, row_plus = 0;
    if (dir == Horizontal)
        col_plus = 1;
    else
        row_plus = 1;
    for (int i = 0; i < size;i++) {
        try {
            Position(pos.row() + i * row_plus, pos.col() + i * col_plus);
        }
        catch (const std::logic_error& e) {
            return false;
        }
    }
    return true;
}
Ship::Ship(const int size, const Position& pos, const Direction& dir) {
    if (!is_collision(size, pos, dir))
        throw std::logic_error("Invalid input: incorrect ship");
    _size = size;
    _position = pos;
    _direction = dir;
}

Ship::Ship(const int size,const char direction,const int row,const char col) {
    Direction tmp_dir;
    if (direction == 'H' || direction == 'h') tmp_dir = Horizontal;
    else if (direction == 'V' || direction == 'v') tmp_dir = Vertical;
    else throw std::logic_error("Invalid input: incorrect ship");
    try {
        Position pos(row, col);
        if (!is_collision(size, pos, tmp_dir))
            throw std::logic_error("Invalid input: incorrect ship");
        _size = size;
        _position = pos;
        _direction = tmp_dir;
    }
    catch (const std::logic_error& e) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
}

Ship::Ship(const std::string& str) {
    parse(str, *this);
}

void Ship::size(const int size) {
    if (size < 1 || size > 4)
        throw std::logic_error("Invalid input: incorrect ship");
    if (!is_collision(size, _position, _direction))
        throw std::logic_error("Invalid input: incorrect ship");
    _size = size;
}

void Ship::row(const int row) {
    try {
        Position tmp(_position);
        tmp.row(row);
        is_collision(_size, tmp, _direction);
        _position.row(row);
    }
    catch (...) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
}

void Ship::col(const int col) {
    try {
        Position tmp(_position);
        tmp.col(col);
        is_collision(_size, tmp, _direction);
        _position.col(col);
    }
    catch (...) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
}

void Ship::col(const char col) {
    try {
        Position tmp(_position);
        tmp.col(col);
        is_collision(_size, tmp, _direction);
        _position.col(col);
    }
    catch (...) {
        throw std::logic_error("Invalid input: incorrect ship");
    }
}

void Ship::direction(const Direction dir) {
    if (!is_collision(_size, _position, dir))
        throw std::logic_error("Invalid input: incorrect ship");
    _direction = dir;
}

void Ship::direction(const char dir) {
    Direction new_dir;
    if (dir == 'H' || dir == 'h') new_dir = Horizontal;
    else if (dir == 'V' || dir == 'v') new_dir = Vertical;
    else throw std::logic_error("Invalid input: incorrect ship");
    if (!is_collision(_size, _position, new_dir))
        throw std::logic_error("Invalid input: incorrect ship");
    _direction = new_dir;
}

void Ship::position(const Position& pos) {
    if (!is_collision(_size, pos, _direction))
        throw std::logic_error("Invalid input: incorrect ship");
    _position = pos;
}

void parse(const std::string& str, Ship& cool_ship) {
    std::istringstream iss(str);
    int size;
    char dir_ch;
    if (!(iss >> size >> dir_ch))
        throw std::logic_error("Invalid input: incorrect ship");

    Direction dir;
    if (dir_ch == 'H' || dir_ch == 'h') dir = Horizontal;
    else if (dir_ch == 'V' || dir_ch == 'v') dir = Vertical;
    else throw std::logic_error("Invalid input: incorrect ship");

    std::string pos_str;
    std::getline(iss >> std::ws, pos_str);
    size_t start = pos_str.find_first_not_of(" \t");
    if (start != std::string::npos)
        pos_str = pos_str.substr(start);

    Position pos;
    try {
        parse(pos_str, pos);
    }
    catch (const std::logic_error&) {
        throw std::logic_error("Invalid input: incorrect ship");
    }

    if (!is_collision(size, pos, dir))
        throw std::logic_error("Invalid input: incorrect ship");

    cool_ship = Ship(size, pos, dir);
}