#include "Entity.h"
#include <iostream>

Point2D Entity::range;

bool Entity::Move(Point2D input) {


	Point2D temp = Pos;
	Pos += input;

	if (Pos.getX() > range.getX()) {
		Pos.setX(range.getX());
	}
	if (Pos.getX() < -range.getX()) {
		Pos.setX(-range.getX());
	}
	if (Pos.getY() > range.getY()) {
		Pos.setY(range.getY());
	}
	if (Pos.getY() < -range.getY()) {
		Pos.setY(-range.getY());
	}

	return Pos == temp; // true result indicates the entity hit the boundary
}

bool Entity::Move(int x, int y) {
	return Move(Point2D(x, y));
}

void Entity::PrintPos(Point2D point) {
	cout << "(" << point.getX() << ", " << point.getY() << ")";
}

void Entity::PosGen() {
	Pos.setX(rand() % (2 * range.getX() + 1)); // get random in [0, 2 * range.getX()]
	Pos.setY(rand() % (2 * range.getY() + 1)); 
	Pos -= range; // shift actuall range to [-range, range]
}

void Entity::RenderAtPos() {
	if (pSprite) {
		GLib::Point2D Offset = { Pos.getX() * 100.0f, Pos.getY() * 100.0f };
		GLib::Render(*pSprite, Offset, 0.0f, 0.0f);
	}
}

//void Entity::SetName() {
//	int i;
//	char c;
//	cin.get(c);
//
//	name[0] = c;
//	//cout << c << endl;
//	for (i = 1; c != '\n'; i++) {
//		cin.get(c);
//		char* tmp = (char*)realloc(name, sizeof(char*) * (static_cast<unsigned long long>(i) + 1));
//		if (tmp != NULL) {
//			name = tmp;
//			name[i] = c;
//		}
//	}
//	if (name != nullptr)name[i - 1] = '\0';
//	//cout << strlen(name) << endl;
//}

Entity::Entity()
{
	PosGen();
}

Entity::~Entity()
{
	if (pSprite != nullptr) GLib::Release(pSprite);
}