#pragma once
#include <cstdlib>
using namespace std;

class Entity
{
public:
	Entity();
	~Entity();
	void Move(int xInput, int yInput);
	void PrintPos();
	void PrintName();

	static int xRange;
	static int yRange;
	
private:
	int x;
	int y;

protected:
	void SetName();
	char* name = (char*)malloc(sizeof(char*));
};

