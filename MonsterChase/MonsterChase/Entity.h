#pragma once
#include <cstdlib>
#include "Engine.h"
using namespace std;

class Entity
{
public:
	Entity();
	~Entity();
	bool Move(int xInput, int yInput);
	void PrintPos();
	void PrintName();

	static int xRange;
	static int yRange;
	Point2D Pos;
	int x;
	int y;

protected:
	void PosGen();
	void SetName();
	char* name = (char*)malloc(sizeof(char*));
	virtual void SetUp() = 0;
};

