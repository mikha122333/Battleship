#pragma once
#include<stdexcept>
#include<string>
#include <sstream>
class Position {
private:
    int _row;
    int _col;
    static const int _max_row;
    static const int _max_col;
    inline bool is_good_col(const int& i)const noexcept { return (i >= 1 && i <= _max_col); }
    inline bool is_good_row(const int& i)const noexcept { return (i >= 1 && i <= _max_row); }
public:
    Position();
    Position(const int &, const int &);
    Position(const Position&);
    friend Position parse(const std::string&);
    Position(const std::string&);
    void row(const int&);
    void col(const int&);
    inline int row() const noexcept { return _row; };
    inline int col() const noexcept { return _col; };
    friend std::string to_string(const Position&)noexcept;
};