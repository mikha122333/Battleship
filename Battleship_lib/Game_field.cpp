#include "Game_field.h"
int Game_field::check_destroy(int row, int col) {//0-9
	int col_plus = 0, row_plus = 0,col_minus=0,row_minus=0;
	int how_big_destroyed_ship=1;
	if (_field[row][col] == '*')
		return 0;
	if (row - 1 >= 0) {
		if (_field[row - 1][col] == 'X')
			row_minus = -1;
		if (_field[row - 1][col] == '*')
			return 0;
	}
	if (col - 1 >= 0 ) {
		if (_field[row][col - 1] == 'X' )
			col_minus = -1;
		if (_field[row][col - 1] == '*')
			return 0;
	}
	if (col + 1 < _col ) {
		if (_field[row][col + 1] == 'X')
			col_plus = 1;
		if (_field[row][col + 1] == '*')
			return 0;
	}
	if (row + 1 < _row ) {
		if (_field[row + 1][col] == 'X')
			row_plus = 1;
		if (_field[row + 1][col] == '*')
			return 0;
	}
	int i = 1;
	while (col_plus * i + col < _col&&(_field[row][col_plus * i + col]!='.'&& _field[row][col_plus * i + col] != ' ')&&col_plus!=0) {
		if (_field[row][col_plus * i + col] == 'X')
			how_big_destroyed_ship++;
		else
			return 0;
		i++;
	}
	i = 1;
	while (row_plus * i + row < _row && (_field[row_plus * i + row][col] != '.' && _field[row_plus * i + row][col] != ' ')&&row_plus != 0) {
		if (_field[row_plus * i + row][col] == 'X')
			how_big_destroyed_ship++;
		else
			return 0;
		i++;
	}
	i = 1;
	while (row+row_minus * i >= 0 && (_field[row + row_minus * i][col] != '.' && _field[row + row_minus * i][col] != ' ')&&row_minus!=0) {
		if (_field[row + row_minus * i][col] == 'X')
			how_big_destroyed_ship++;
		else
			return 0;
		i++;
	}
	1;
	while (col_minus * i + col < _col && (_field[row][col_minus * i + col] != '.' && _field[row][col_minus * i + col] != ' ')&&col_minus!=0) {
		if (_field[row][col_minus * i + col] == 'X')
			how_big_destroyed_ship++;
		else
			return 0;
		i++;
	}
	return how_big_destroyed_ship;
}
Game_field::Game_field():_row(10),_col(10) {
	_field = new char* [_row];
	for (int i = 0; i < _row; i++) {
		_field[i] = new char[_col];
		for (int i2 = 0; i2 < _col; i2++) {
			_field[i][i2] = ' ';
		}
	}
}
Game_field::~Game_field() {
	for (int i = 0; i < _row; i++) {
		delete[] _field[i];
	}
	delete[] _field;
}
void Game_field::set(const Ship& ship) {
	int plus_row = 0, plus_col = 0;
	if (ship.direction() == Horizontal)
		plus_col = 1;
	else
		plus_row = 1;
	if(!is_collision(*this,ship))
		throw std::logic_error("Invalid input: incorrect field");
	for (int i = 0; i < ship.size(); i++) {
		_field[ship.row() + i * plus_row-1][ship.col() + i * plus_col-1] = '*';
	}
}
State Game_field::set(int raw, char col) {//1-10
	if (raw<1 || raw>_row || col<'A' || col>('A' + _col - 1))
		throw std::logic_error("Invalid input: incorrect move");
	if (_field[raw - 1][col - 'A'] == '*') {
		_field[raw-1][col-'A'] = 'X';
		switch (check_destroy(raw - 1, col - 'A')) {
		case 0:return Hit;
		case 1:return BoatDestroyed;
		case 2:return DestroyersDestroyed;
		case 3:return CruisersDestroyed;
		case 4:return BattleshipDestroyed;
		}
	}
	else return Missed;
}
std::string to_string(const Game_field& game_field, bool to_show_ships) {
	std::string str;
	str+= "  |";
	for (int i = 0; i < game_field._col-1; i++) {
		str += " ";
		str+= ('A' + i);
	}
	str += " ";
	str += ('A' + game_field._col - 1);
	str += "|\n";
	for (int i = 0; i < game_field._row; i++) {
		if(i<9)
			str+=std::to_string( i + 1) + " |";
		else
			str += std::to_string(i + 1) + "|";
		for (int i2 = 0; i2 < game_field._col; i2++) {
			if (game_field._field[i][i2] == '*')
				if (to_show_ships == 1) {
					str += game_field._field[i][i2];
					str += "|";
				}
				else
					str += " |";
			else {
				str += game_field._field[i][i2];
				str+="|";
			}
		}
		str += '\n';
	}
	str += "  +";
		for (int i = 0; i < game_field._col-1; i++) {
			str += "--";
		}
	str += "-+\n";
	return str;
}
std::string to_string(const Game_field& game_field) {
	return to_string(game_field, 0);
}
bool is_collision(const Game_field& game_field, const Ship& ship) {
	int plus_row = 0, plus_col = 0;
	if (ship.direction() == Horizontal)
		plus_col = 1;
	else
		plus_row = 1;
	for (int i = 0; i < ship.size(); i++) {
		for (int row = -1; row <= 1; row++) {
			for (int col = -1; col <= 1; col++) {
				if (ship.col() + col + plus_col * i -1>= 0 && ship.row() + row + plus_row * i-1 >= 0 && ship.col() + col + plus_col * i-1 < game_field._col && ship.row() + row + plus_row * i-1 < game_field._row) {
					if (game_field._field[ship.row() + row + plus_row * i-1][ship.col() + col + plus_col * i-1] == '*')
						return false;
				}
			}
		}
	}
	return true;
}