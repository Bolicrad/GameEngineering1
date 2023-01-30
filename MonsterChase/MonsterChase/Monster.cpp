#include "Monster.h"
#include <iostream>

Monster::Monster() {
	SetUp();
}

Monster::~Monster() {
	cout << "Monster " << GetName() << " deleted" << endl;
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
	cout << "Monster " << GetName() << " died because of " << reason << "." << endl;
	cout << "Generating new Monster..." << endl;
	PosGen();
	SetUp();
}

const char* Monster::GetName() {
	if (name != nullptr) {
		if (*name != '\0') {
			return name;
		}
	}
	return "Monster";
}

void Monster::SetUp() {
	//cout << "Enter Monster name: ";
	//SetName();
	cout << "Monster " << GetName() << " initiated, position: ";
	PrintPos(Pos);
	cout << endl;
}