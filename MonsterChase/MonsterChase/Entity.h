#pragma once
#include <cstdlib>
#include "Engine.h"
using namespace std;

class Entity
{
public:
	Entity();
	~Entity();
	bool Move(Point2D input);
	bool Move(int x, int y);
	void PrintPos(Point2D point);
	void PrintName();

	static Point2D range;
	Point2D Pos;

protected:
	void PosGen();
	void SetName();
	char* name = (char*)malloc(sizeof(char*));
	virtual void SetUp() = 0;
};

