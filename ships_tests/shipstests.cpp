// ConsoleApplication30.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Player.h"
#include "Ship.h"
#include "SafetyChecks.h"

#include <string>

using namespace std;

int size_of_board = 13;

void initialize(Player& player1, Player& player2) {
	//init players
	player1.number = 1;
	player2.number = 2;

	//reading board_size into players
	player1.board_size = player2.board_size = size_of_board;

	player1.boardInit();
	player2.boardInit();
}

void insertShips(Player& player) {
	int number = 1;

	for (auto& ship : player.ships) {

		bool input_valid = false;

		while (!input_valid) {
			cout << ship.type << " which size is " << ship.size << " units." << endl;

			cout << "Enter starting position of the ship: ";
			string pos;
			cin >> pos;

			input_valid = inputValid(player, ship, pos, size_of_board);

		}

		player.boardAddShip(ship.size, ship.x_position, ship.y_position, ship.direction, number);
		player.ship_parts_left[number - 1][0] = number;
		player.ship_parts_left[number - 1][1] = ship.size;

		number++;
	}
}


void isDestroyed(Player& player, int x_value) {

	int ship_s = (player.ships.begin()+x_value)->size;

	Ship temp_ship;

	temp_ship = player.ships.at(x_value);

	int ship_size = temp_ship.size;
	int ship_x_pos = temp_ship.x_position;
	int ship_y_pos = temp_ship.y_position;
	char ship_dir = temp_ship.direction;

	for (auto i = 0; i < ship_size; ++i) {
		if (ship_dir == 'V') {
			player.board_for_enemy[ship_x_pos + i][ship_y_pos] = "D";
			player.board[ship_x_pos + i][ship_y_pos] = "D";
		}
		else {
			player.board_for_enemy[ship_x_pos][ship_y_pos + i] = "D";
			player.board[ship_x_pos][ship_y_pos + i] = "D";
		}
	}

}


//attack WHO, not who attacks
int attack(Player& player, string where) {
	
	int y = get_y_cord(where);

	int x = get_x_cord(where);

	if (player.board[x][y] == "~") {
		player.board[x][y] = "0";
		player.board_for_enemy[x][y] = "0";
		return 0;
	}
	else if (player.board[x][y] == "1" ||
		player.board[x][y] == "2" || player.board[x][y] == "3" || 
		player.board[x][y] == "4" || player.board[x][y] == "5") {

		int ship_number = stoi(player.board[x][y]);
		ship_number -= 1;

		player.ship_parts_left[ship_number][1] -= 1;

		if (player.ship_parts_left[ship_number][1] < 1) {
			isDestroyed(player, ship_number);
		}
		else {
			player.board[x][y] = "X";
			player.board_for_enemy[x][y] = "X";
		}

		player.pieces_left -= 1;
		
		if (player.pieces_left < 1) {
			cout << "You have finished your opponent! All the pieces have been destroyed!" << endl;
			exit(0);
		}

		return 1;
	}
	else if (player.board[x][y] == "X" || player.board[x][y] == "D") {
		return 2;
	}
	else {
		return 3;
	}
}


int shooting(Player& player1, Player& player2) {

	bool game_on = true;
	int player_n = 2;

	while (game_on == true && (player_n == 1 || player_n == 2)) {

		string where;
		int result;

		if (player_n == 1) {
			cout << "Player 1 attacking!" << endl;
			player2.boardForEnemyShow();
			cout << "Where do you want to shot?: ";
			cin >> where;
			result = attack(player2, where);
		}
		else {
			cout << "Player 2 attacking!" << endl;
			player1.boardForEnemyShow();
			cout << "Where do you want to shot?: ";
			cin >> where;
			result = attack(player1, where);
		}

		switch (result) {
		case 0:
			cout << "You missed!" << endl << endl;
			player_n += 1;
			break;
		case 1:
			cout << "An enemy ship has been hit!" << endl;
			break;
		case 2:
			cout << "You have already attacked that square! Attack another one." << endl;
			break;
		case 3:
			cout << "Something went wrong, try again.";
			break;
		} 

		if (player_n > 2)
			player_n = 1;
	}
	return 1;
}


int main()
{
	Player player1, player2;
	initialize(player1, player2);

	player1.shipsInit();
	player2.shipsInit();

	cout << endl << "Player 1!\nInsert your ships!" << endl << endl;
	player1.boardShow();
	insertShips(player1);

	cout << endl << "Player 2!\nInsert your ships!" << endl << endl;
	player2.boardShow();
	insertShips(player2);
	
	int who_won = shooting(player1, player2);
	
	return 0;
}

