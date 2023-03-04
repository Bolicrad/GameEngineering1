#include "Player.h"
#include <iostream>
using namespace std;

Player::Player() {
	SetUp();

	pSprite = CreateSprite("data\\GoodGuy.dds");
}

Player:: ~Player() {
	cout << "Player " << GetName() << " died, Game Over" << endl;
}

void Player::SetUp() {
	cout << "Player " << GetName() << " initiated, position: ";
	PrintPos(Pos);
	cout << endl;
}

const char* Player::GetName() {
	return "Player";
}

Player* Player::player;