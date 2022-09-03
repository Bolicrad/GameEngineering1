#include "Player.h"
#include <iostream>
using namespace std;

Player::Player() {
	SetUp();
}

Player:: ~Player() {
	cout << "Player " << name << " died, Game Over" << endl;
}

void Player::SetUp() {
	cout << "Enter Player name: ";
	SetName();
	cout << "Player " << name << " initiated, position: ";
	PrintPos();
}

Player* Player::player;