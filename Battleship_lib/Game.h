#pragma once
#include "Player.h"
#include<sstream>
#include <cstdlib>
#include <ctime>
#include<string>
#include<stdexcept>
#include<iostream>
class Game {
private:
    Player _user;
    Player _computer;
    void user_init(const std::string& user);
    void computer_init(const std::string& comp);
    bool is_end()noexcept;
    void show_game_window()noexcept;
    State user_move(const std::string& input);
    State computer_move();
public:
    Game();
    void start();
};

