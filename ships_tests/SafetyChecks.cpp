#include "stdafx.h"
#include "SafetyChecks.h"
#include "Player.h"
#include "Ship.h"

#include <string>
#include <iostream>

using namespace std;


int get_y_cord(string where) {
	char ch = where[0];
	if (!isupper(ch))
		toupper(ch);

	int y = ch - 'A' + 1;
	return y;
}

int get_x_cord(string where) {

	int x;
	if (where[2]) {
		int x_1 = where[1] - '0';
		x_1 *= 10;
		int x_2 = where[2] - '0';
		x = x_1 + x_2;
	}
	else
		x = where[1] - '0';

	return x;
}


bool cordsValid(int x, int y, int size_of_board) {

	if (x > 0 && x < size_of_board && y > 0 && y < size_of_board)
		return true;
	else
		return false;

}

bool dirValid(char d) {

	if (d == 'V' || d == 'v' || d == 'H' || d == 'h')
		return true;
	else
		return false;

}

bool posValid(int x, int y, char d, int size) {

	if (d == 'V') {
		if ((x + size) > 12)
			return false;
	}
	else {
		if ((y + size) > 12)
			return false;
	}

	return true;
}

bool boardValid(Player& player, int x, int y, char d, int size) {

	for (int i = 0; i < size; ++i) {

		string value;

		if (d == 'V') {
			value = player.board[x + i][y];
		}
		else {
			value = player.board[x][y + i];
		}

		if (value == "1" || value == "2" || value == "3" || value == "4" || value == "5") {
			return false;
		}

	}
	return true;
	cout << endl;
}


bool inputValid(Player& player, Ship& ship, string pos, const int size_of_board) {

	bool cords_valid = false;
	bool dir_valid = false;
	bool position_valid = false;

	int x, y;
	char dir;

	while (!pos[1]) {
		cout << "You have entered invalid position. Try again: ";
		cin >> pos;
	}

	while (!position_valid) {

		while (!cords_valid) {

			x = get_x_cord(pos);
			y = get_y_cord(pos);

			if (cordsValid(x, y, size_of_board)) {
				cords_valid = true;
			}
			else {
				cin.clear();

				cout << "You have entered invalid position. Try again: ";
				cin >> pos;
			}

		}

		cout << "Enter the direction the ship should be set: vertical [V] or horizontal [H]: ";
		cin >> dir;


		while (!dir_valid) {

			if (dirValid(dir)) {
				dir_valid = true;
			}
			else {
				cin.clear();
				cout << "You have entered invalid direction, please try again: vertical [V] or horizontal [H]: ";
				cin >> dir;
			}
		}

		if (posValid(x, y, dir, ship.size) && boardValid(player, x, y, dir, ship.size)) {
			position_valid = true;
		}
		else {
			cout << "The ship will be out of the board or it was going to be placed on another's ship "
				<< "place, please try another positon/direction" << endl << endl;
			return false;
		}

	}
	ship.x_position = x;
	ship.y_position = y;

	ship.setDirection(dir);

	return true;


}
