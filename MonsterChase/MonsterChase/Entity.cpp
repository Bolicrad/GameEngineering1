
#include "Entity.h"
#include <iostream>

int Entity::xRange = 0;
int Entity::yRange = 0;

bool Entity::Move(int x, int y) {
	int xTemp = this->x;
	int yTemp = this->y;

	this->x += x;
	this->y += y;

	bool stroke = true;
	
	if (this->x > xRange) this->x = xRange;
	else if (this->x < -xRange) this->x = -xRange;
	else if (this->y > yRange) this->y = yRange;
	else if (this->y < -yRange) this->y = -yRange;
	else stroke = false;

	cout << name;
	if (this->x == xTemp && this->y == yTemp) {
		cout << " stays at ";
	}
	else cout << " moved to ";
	PrintPos();

	return stroke;
}

void Entity::PrintPos() {
	cout << "(" << x << ", " << y << ")" << endl;
}

void Entity::PrintName() {
	cout << name;
}

void Entity::PosGen() {
	x = rand() % (2 * xRange + 1) - xRange;
	y = rand() % (2 * yRange + 1) - yRange;
}

void Entity::SetName() {
	int i;
	char c;
	cin.get(c);
	name[0] = c;
	//cout << c << endl;
	for (i = 1; c != '\n'; i++) {
		cin.get(c);
		name = (char*)realloc(name, sizeof(char*) * (i + 1));
		name[i] = c;
	}
	name[i - 1] = '\0';
	//cout << strlen(name) << endl;
}

Entity::Entity()
{
	PosGen();
}

Entity::~Entity()
{
}