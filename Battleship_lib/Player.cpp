#include "Player.h"
const int Player::_max_ships_counts[4] = { 4, 3, 2, 1 };
Player::Player() {
    for (int i = 0; i < 4; i++) {
        _ships_counts[i] = 0;
    }
}
void Player::set_ship(const Ship& ship) {
    if ((_ships_counts[ship.size() - 1] + 1) > _max_ships_counts[ship.size() - 1])
        throw std::logic_error("Invalid input: incorrect field");
    try {
        _gamefield.set(ship);
    }
    catch (std::logic_error) {
        throw std::logic_error("Invalid input: incorrect field");
    }
    _ships_counts[ship.size() - 1]++;
}
State Player::set_action(const int row, const char col) {
    State res;
    try {
        res = _gamefield.set(row, col);
    }
    catch (std::logic_error) {
        throw std::logic_error("Invalid input: incorrect move");
    }
    switch (res) {
    case BoatDestroyed:_ships_counts[0]--; break;
    case DestroyersDestroyed:_ships_counts[1]--; break;
    case CruisersDestroyed:_ships_counts[2]--; break;
    case BattleshipDestroyed:_ships_counts[3]--; break;
    }
    return res;
}
void Player::show_field(const bool hide_ships)const noexcept {
    std::string res;
    std::cout << (to_string(_gamefield, hide_ships));
    res += "\nShips Left:\n";
    for (int i = 0; i < 4; i++) {
        for (int i2 = 0; i2 < (i + 1); i2++) {
            res += "*";
        }
        res += " - ";
        res += std::to_string(_ships_counts[i]);
        if ((i + 1) < 4)
            res += " ";
    }
    std::cout << res;
}
bool Player::check_lose()const noexcept {
    for (int i = 0; i < 4; i++) {
        if (_ships_counts[i] > 0)
            return 0;
    }
    return 1;
}
bool Player::check_ready()const noexcept {
    for (int i = 0; i < 4; i++) {
        if (_ships_counts[i] < _max_ships_counts[i])
            return 0;
    }
    return 1;
}