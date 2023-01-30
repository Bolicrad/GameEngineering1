#pragma once
#include <cstdlib>
#include "Engine.h"
#include "Helper.h"
using namespace std;

class Entity
{
public:
	Entity();
	~Entity();
	bool Move(Point2D input);
	bool Move(int x, int y);
	void PrintPos(Point2D point);
	void RenderAtPos();
	virtual const char* GetName() = 0;

	static Point2D range;
	Point2D Pos;
	

protected:
	void PosGen();
	virtual void SetUp() = 0;
	GLib::Sprite* pSprite;
};

