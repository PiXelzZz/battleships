#include "stdafx.h"
#include "Ship.h"
#include <string>

using namespace std;

Ship::Ship() {

}

Ship::~Ship() {

}

void Ship::setType(string ship_type) {

	for (auto iter : ship_types) {
		if (ship_type == iter.first) {
			type = iter.first;
			size = iter.second;
			parts_left = size;
			break;
		}
	}
}

void Ship::setDirection(char d) {

	switch (d) {
	case 'H':
	case 'h':
		direction = 'H';
		break;
	case 'V':
	case 'v':
		direction = 'V';
		break;
	}
}