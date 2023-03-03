#pragma once
#include <cstdlib>
#include "Engine.h"

class Actor:
	public Engine::Entity
{
public:
	Actor();
	bool Move(Point2D input);
	bool Move(int x, int y);
	virtual const char* GetName() = 0;
	static Point2D range;

protected:
	virtual void SetUp() = 0;
	void PosGen();
};

