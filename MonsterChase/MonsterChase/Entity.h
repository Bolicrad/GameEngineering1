#pragma once
#include <cstdlib>
using namespace std;

class Entity
{
public:
	Entity();
	~Entity();
	void Move(int xInput, int yInput);
	void Print();
	void SetName();
	static int xRange;
	static int yRange;
	
private:
	int x;
	int y;

protected:
	char* name = (char*)malloc(sizeof(char*));
};

