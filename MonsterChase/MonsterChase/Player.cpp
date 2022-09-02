#include "Player.h"
#include <iostream>
using namespace std;
Player::Player()
{
	cout << "Enter Player name: ";
	SetName();
	cout << "Player " << name << " initiated, position: ";
	Entity::Print();
}

Player:: ~Player() {
	cout << "Player " << name << " died, Game Over" << endl;
}
