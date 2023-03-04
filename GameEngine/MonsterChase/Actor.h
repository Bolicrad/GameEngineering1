#pragma once
#include "Engine.h"

class Actor:
	public Engine::Entity<int>
{
public:
	Actor();
	bool Move(Point2D<int> input);
	bool Move(int x, int y);
	virtual const char* GetName() = 0;
	static Point2D<int> range;

protected:
	virtual void SetUp() = 0;
	void PosGen();
};

