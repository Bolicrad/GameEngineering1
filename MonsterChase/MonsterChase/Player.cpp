#include "Player.h"
#include <iostream>
using namespace std;

Player::Player() {
	SetUp();
}

Player:: ~Player() {
	cout << "Player " << GetName() << " died, Game Over" << endl;
}

void Player::SetUp() {
	cout << "Enter Player name: ";
	SetName();
	cout << "Player " << GetName() << " initiated, position: ";
	PrintPos(Pos);
	cout << endl;
}

const char* Player::GetName() {
	if (name != nullptr) {
		if (*name != '\0') {
			return name;
		}
	}
	return "Player";
}

Player* Player::player;