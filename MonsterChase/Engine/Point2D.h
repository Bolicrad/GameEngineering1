#pragma once
class Point2D
{
public:

	Point2D(int i_x = 0, int i_y = 0) :
		x(i_x),
		y(i_y)
	{}
	
	int getX(void) const { return x; }
	int getY(void) const { return y; }

	void setX(int input) { x = input; }
	void setY(int input) { y = input; }

	inline bool operator==(const Point2D& rhs) const;
	inline bool operator!=(const Point2D& rhs) const;
	inline const Point2D operator+(const Point2D& rhs) const;
	inline const Point2D operator-() const;
	inline const Point2D operator-(const Point2D& rhs) const;
	inline const Point2D operator*(int rhs) const;
	inline const Point2D operator/(int rhs) const;
	inline Point2D& operator=(const Point2D& rhs);
	inline Point2D& operator+=(const Point2D& rhs);
	inline Point2D& operator-=(const Point2D& rhs);
	inline Point2D& operator*=(int rhs);
	inline Point2D& operator/=(int rhs);

	static const Point2D zero;
	
private:
	int x;
	int y;
};

#include "Point2D-inl.h" 