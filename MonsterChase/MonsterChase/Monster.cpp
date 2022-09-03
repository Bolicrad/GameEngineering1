#include "Monster.h"
#include <iostream>
Monster::Monster() {
	
	cout << "Enter Monster name: ";
	SetName();
	cout << "Monster " << name << " initiated, position: ";
	PrintPos();
}

Monster::~Monster() {
	cout << "Monster " << name << " deleted" << endl;
}

Monster *Monster::monsters;