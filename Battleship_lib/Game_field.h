#pragma once
#include<iostream>
#include<iomanip>
#include<string>
enum State { Missed, BoatDestroyed, DestroyersDestroyed, CruisersDestroyed, BattleshipDestroyed, Hit };
#include "Ship.h"
class Game_field {
private:
	char** _field;           
	const int _row;            
	const int _col; 
	int check_destroy(int row, int col);
public:
	Game_field();
	~Game_field();
	void set(const Ship& ship);
	State set(int, char);
	friend std::string to_string(const Game_field& game_field, bool to_show_ships);
	friend std::string to_string(const Game_field& game_field);
	friend bool is_collision(const Game_field& game_field, const Ship& ship);
};