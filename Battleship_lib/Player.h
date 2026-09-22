#pragma once
#include <cstdlib>
#include <ctime>
#include<string>
#include<stdexcept>
#include<sstream>
#include<iostream>
#include "Game_field.h"
class Player {
private:
    Game_field _gamefield;
    int _ships_counts[4];    // count of player ships different sizes
    static const int _max_ships_counts[4];
public:
    Player();
    void set_ship(const Ship& ship);
    State set_action(const int, const char);
    void show_field(const bool hide_ships = false)const noexcept;
    bool check_lose()const noexcept;
    bool check_ready()const noexcept;
};
