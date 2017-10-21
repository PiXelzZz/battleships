#pragma once
#ifndef SAFETY_CHECKS_H
#define SAFETY_CHECKS_H

#include <string>
#include "Ship.h"
#include "Player.h"

int get_y_cord(std::string where);
int get_x_cord(std::string where);

bool cordsValid(int x, int y, int size_of_board);
bool dirValid(char d);
bool posValid(int x, int y, char d, int size);

bool inputValid(Player& player, Ship& ship, std::string pos, const int size_of_board);
bool boardValid(Player& player, int x, int y, char d, int size);

#endif