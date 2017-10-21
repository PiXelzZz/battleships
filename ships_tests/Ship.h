#pragma once
#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <map>
#include <vector>

class Ship
{
public:
	Ship();
	~Ship();

	std::map< std::string, int> ship_types{
		{ "Battleship", 5 },
		{ "Carrier", 4 },
		{ "Destroyer", 3 },
		{ "Patrol boat", 3 },
		{ "Submarine", 2 }
	};

	std::string type;
	int size;
	int x_position;
	int y_position;
	char direction;
	int parts_left;

	void setType(std::string ship_type);
	void setPosition(std::string pos);
	void setDirection(char d);

};

#endif