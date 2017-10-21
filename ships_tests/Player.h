#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Ship.h"
#include <string>
#include <map>

class Player
{
public:
	Player();
	~Player();

	int number;
	std::vector<Ship> ships;
	int board_size = 13;
	std::string board[13][13];
	std::string board_for_enemy[13][13];
	int pieces_left = 0;
	int ship_parts_left[5][2];

	void addShip(Ship ship);
	void boardInit();
	void boardShow();
	void boardForEnemyShow();
	void boardAddShip(int size, int x_position, int y_position, char direction, int number);

	void shipsInit();
};

#endif