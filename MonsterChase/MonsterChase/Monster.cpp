#include "Monster.h"
#include <iostream>

Monster::Monster() {
	SetUp();
}

Monster::~Monster() {
	cout << "Monster " << name << " deleted" << endl;
}

Monster *Monster::monsters;
int Monster::monsterCount = 0;

void Monster::Wander() {
	int x = rand() % 3 - 1;
	int y = rand() % 3 - 1;
	if (Move(x, y)) {
		Rebirth("stroke into boundary");
	}
}

void Monster::Rebirth(const char* reason) {
	cout << "Monster " << name << " died because of " << reason << "." << endl;
	cout << "Generating new Monster..." << endl;
	PosGen();
	SetUp();
}

void Monster::SetUp() {
	cout << "Enter Monster name: ";
	SetName();
	cout << "Monster " << name << " initiated, position: ";
	PrintPos(Pos);
	cout << endl;
}