#include "Game.h"
void Game::user_init(const std::string& user) {
    _user.set_ship(user);
}
void Game::computer_init(const std::string& comp) {
    _computer.set_ship(comp);
}
bool Game::is_end()noexcept {
    return((_computer.check_lose()) || (_user.check_lose()));
}
void Game::show_game_window()noexcept {
    std::cout << "= COMPUTER GAME FIELD =\n\n";
    _user.show_field();
    std::cout << "\n=== YOUR PLAY FIELD ===\n\n";
    _computer.show_field(1);
    std::cout << '\n';
}
State Game::user_move(const std::string& input) {
    std::istringstream iss(input);
    int row;
    char col;
    iss >> row >> col;
    State res;
    try {
        res = _computer.set_action(row, col);
    }
    catch (std::logic_error) {
        throw std::logic_error("Invalid input: incorrect move");
    }
    return res;
}
State Game::computer_move() {
    bool f = 1;
    State res;
    for (int i = 0; i < 10 && f; i++) {
        try {
            f = 0;
            res = _user.set_action(1 + i, 'A' + i);
        }
        catch (std::logic_error) {
            f = 1;
        }
    }
    if (f == 0)
        return res;
    for (int i = 0; i < 10 && f; i++) {
        try {
            f = 0;
            res = _user.set_action(1 + i, 'A' + 9 - i);
        }
        catch (std::logic_error) {
            f = 1;
        }
    }
    if (f == 0)
        return res;
    for (int row = 0; row < 10 && f; row++) {
        for (int col = 0; col < 10 && f; col++) {
            try {
                f = 0;
                res = _user.set_action(row + 1, 'A' + col);
            }
            catch (std::logic_error) {
                f = 1;
            }
        }
    }
    if (f == 0)
        return res;
    else
        throw std::logic_error("Invalid input: incorrect move");
}
Game::Game() :_user(), _computer() {
    //_user=Player();
    //_computer=Player();
}
void Game::start() {
    std::string tmp;
    std::string input;
    try {
        while (!_user.check_ready()) {
            _user.show_field(1);
            std::cout << std::endl;
            std::getline(std::cin, input);
            if (input == "\n")
                throw std::logic_error("Invalid input: incorrect field");
            else
                user_init(input);
            system("cls");
        }
        _user.show_field(1);
        std::cout << "\n enter when ready to put computer ships";
        std::getline(std::cin, input);
        system("cls");
        while (!_computer.check_ready()) {
            _computer.show_field(1);
            std::cout << std::endl;
            std::getline(std::cin, input);
            if (input == "\n")
                throw std::logic_error("Invalid input: incorrect field");
            else
                computer_init(input);
            system("cls");
        }
        _computer.show_field(1);
        std::cout << std::endl;
        std::cout << "enter when ready";
        std::getline(std::cin, input);
        system("cls");
    }
    catch (std::logic_error) {
        throw std::logic_error("Invalid input: incorrect field");
    }
    try {
        while (!is_end()) {
            while (!is_end()) {
                show_game_window();
                std::getline(std::cin, input);
                system("cls");
                if (user_move(input) == Missed)
                    break;

            }
            while (!is_end()) {
                show_game_window();
                if (computer_move() == Missed) {
                    system("cls");
                    break;
                }
            }
        }
    }
    catch (std::logic_error) {
        //system("clear");
        //std::cout<<"\033c";
        throw std::logic_error("Invalid input: incorrect move");
    }
    std::cout << "\n";
    show_game_window();
    std::cout << "\n";
    if (_computer.check_lose())
        std::cout << "USER WIN!";
    else
        std::cout << "COMPUTER WIN!";
}
