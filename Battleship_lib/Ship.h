#pragma once
#include <string>
#include <stdexcept>
#include <sstream>
#include "Position.h"
enum Direction { Horizontal, Vertical };
class Ship {
private:
    int _size;
    Position _position;
    Direction _direction;

public:
    Ship(const int size, const Position& pos, const Direction& dir);
    Ship(const int size, const char direction, const int row,const char col);
    Ship(const std::string& str);

    inline int size() const noexcept { return _size; }
    inline int row() const noexcept { return _position.row(); }
    inline int col() const noexcept { return _position.col(); }
    inline Position position() const noexcept { return _position; }
    inline Direction direction() const noexcept { return _direction; }

    void size(const int size);
    void row(const int row);
    void col(const int col);
    void col(const char col);
    void direction(const Direction dir);
    void direction(const char dir);
    void position(const Position& pos);

    friend void parse(const std::string& str, Ship& ship);
    friend bool is_collision(const int size, const Position& pos, const Direction dir) noexcept;

};