#pragma once
#include "Player.h"
class Game {
private:
    Player _user;
    Player _computer;
    inline void user_init(const std::string& user) { _user.set_ship(user); }
    inline void computer_init(const std::string& comp) { _computer.set_ship(comp); }
    inline bool is_end()noexcept { return((_computer.check_lose()) || (_user.check_lose())); }
    void show_game_window()noexcept;
    State user_move(const std::string& input);
    State computer_move();
public:
    Game() :_user(), _computer() {}
    void start();
};

