#include "Monster.h"
#include <iostream>
Monster::Monster() {
	
	cout << "Enter Monster name: ";
	SetName();
	cout << "Monster " << name << " initiated, position: ";
	Print();
}

Monster::~Monster() {

}