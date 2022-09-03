#include "Player.h"
#include <iostream>
using namespace std;
Player::Player()
{
	cout << "Enter Player name: ";
	SetName();
	cout << "Player " << name << " initiated, position: ";
	PrintPos();
}

Player:: ~Player() {
	cout << "Player " << name << " died, Game Over" << endl;
}

Player* Player::player;