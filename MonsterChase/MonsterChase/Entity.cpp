
#include "Entity.h"
#include <iostream>

int Entity::xRange = 0;
int Entity::yRange = 0;

void Entity::Move(int xInput, int yInput) {
	this->x += xInput;
	this->y += yInput;
	if (this->x > xRange) this->x = xRange;
	if (this->x < -xRange) this->x = -xRange;
	if (this->y > yRange) this->y = yRange;
	if (this->y < -yRange) this->y = -yRange;
	cout << name << " moved to ";
	PrintPos();
}

void Entity::PrintPos() {
	cout << "(" << x << ", " << y << ")" << endl;
}

void Entity::PrintName() {
	cout << name;
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
	this->x = rand() % (2 * xRange + 1) - xRange;
	this->y = rand() % (2 * yRange + 1) - yRange;
}

Entity::~Entity()
{
}