#include "stdafx.h"
#include "Player.h"
#include <string>
#include <sstream>
#include <iostream>
#include "Ship.h"

using namespace std;

Player::Player()
{
}


Player::~Player()
{
}

void Player::addShip(Ship ship) {

	ships.push_back(ship);

}

void Player::boardInit() {

	board[0][0] = "/";
	board_for_enemy[0][0] = board[0][0];
	

	for (auto i = 1; i < board_size; ++i) {

		stringstream ss;
		string str;
		char letter = 'A' + (i - 1);
		ss << letter;
		ss >> str;

		board[0][i] = str;
		board[i][0] = to_string(i);

		board_for_enemy[0][i] = board[0][i];
		board_for_enemy[i][0] = board[i][0];
	}

	for (auto i = 1; i < board_size; ++i) {
		for (auto j = 1; j < board_size; ++j) {
			board[i][j] = "~";
			board_for_enemy[i][j] = board[i][j];
		}
	}
}


void Player::boardShow() {
	for (auto i = 0; i < board_size; ++i) {
		if (i < 10)
			cout << " ";

		for (auto j = 0; j < board_size; ++j) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


void Player::boardForEnemyShow() {
	for (auto i = 0; i < board_size; ++i) {
		if (i < 10)
			cout << " ";

		for (auto j = 0; j < board_size; ++j) {
			cout << board_for_enemy[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}



void Player::boardAddShip(int size, int x_position, int y_position, char direction, int number) {
	for (int i = 0; i < size; ++i) {
		int x = x_position;
		int y = y_position;

		if (direction == 'V')
			x += i;
		else
			y += i;

		char val = '0' + number;
		board[x][y] = val;

		pieces_left += 1;

	}
	boardShow();
}


void Player::shipsInit() {
	Ship ship;

	for (auto iter : ship.ship_types) {
		Ship new_ship;
		new_ship.setType(iter.first);
		this->addShip(new_ship);

	}
}

