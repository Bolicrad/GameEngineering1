#pragma once
class Point2D
{
public:

	Point2D(int i_x = 0, int i_y = 0) :
		x(i_x),
		y(i_y)
	{}
	
	int getX() { return x; }
	int getY() { return y; }

	void setX(int input) { x = input; }
	void setY(int input) { y = input; }

	bool operator==(Point2D rhs);
	bool operator!=(Point2D rhs);
	Point2D operator+(Point2D rhs);
	Point2D operator-();
	Point2D operator-(Point2D rhs);
	Point2D operator*(int rhs);
	Point2D operator/(int rhs);
	Point2D& operator=(Point2D rhs);
	Point2D& operator+=(Point2D rhs);
	Point2D& operator-=(Point2D rhs);
	Point2D& operator*=(int rhs);
	Point2D& operator/=(int rhs);

	static Point2D zero;
	
private:
	int x;
	int y;
};

inline Point2D operator*(int lhs, Point2D rhs) { return rhs * lhs; }