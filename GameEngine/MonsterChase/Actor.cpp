#include "Actor.h"

Point2D<int> Actor::range;

bool Actor::Move(Point2D<int> input) {


	Point2D<int> temp = Pos;
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

bool Actor::Move(int x, int y) {
	return Move(Point2D<int>(x, y));
}

void Actor::PosGen() {	
	Pos.setX(rand() % (2 * range.getX() + 1)); // get random in [0, 2 * range.getX()]
	Pos.setY(rand() % (2 * range.getY() + 1));
	Pos -= range; // shift actuall range to [-range, range]
}

Actor::Actor()
{
	PosGen();
}