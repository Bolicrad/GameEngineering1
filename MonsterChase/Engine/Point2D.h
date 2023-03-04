#pragma once
template <typename T>
class Point2D
{
public:

	Point2D(int i_x = 0, int i_y = 0) :
		x(i_x),
		y(i_y)
	{}
	
	T getX(void) const { return x; }
	T getY(void) const { return y; }

	void setX(T input) { x = input; }
	void setY(T input) { y = input; }

	//equality
	inline bool operator==(const Point2D& rhs) const {
		return x == rhs.getX() && y == rhs.getY();
	};

	//inequality
	inline bool operator!=(const Point2D& rhs) const {
		return !(*this == rhs);
	};

	//Point2D + Point2D
	inline const Point2D<T> operator+(const Point2D& rhs) const {
		return Point2D(x + rhs.getX(), y + rhs.getY());
	};

	//negate
	inline const Point2D<T> operator-() const {
		return Point2D(-x, -y);
	};

	//Point2D - Point2D
	inline const Point2D<T> operator-(const Point2D& rhs) const {
		return Point2D(x - rhs.getX(), y - rhs.getY());
	};

	//Point2D * valueType
	inline const Point2D<T> operator*(T rhs) const {
		return Point2D(x * rhs, y * rhs);
	};

	//Point2D / valueType
	inline const Point2D<T> operator/(T rhs) const {
		return Point2D(x / rhs, y / rhs);
	};

	//Direct Assignment
	inline Point2D<T>& operator=(const Point2D& rhs) {
		x = rhs.getX();
		y = rhs.getY();
		return *this;
	};

	//Point2D += Point2D
	inline Point2D<T>& operator+=(const Point2D& rhs) {
		x += rhs.getX();
		y += rhs.getY();
		return *this;
	};

	//Point2D -= Point2D
	inline Point2D<T>& operator-=(const Point2D& rhs) {
		x -= rhs.getX();
		y -= rhs.getY();
		return *this;
	};

	//Point2D *= valueType
	inline Point2D<T>& operator*=(T rhs) {
		*this = *this * rhs;
		return *this;
	};

	//Point2D /= valueType
	inline Point2D<T>& operator/=(T rhs) {
		*this = *this / rhs;
		return *this;
	};

	static const Point2D<T> zero;
	
private:
	T x;
	T y;
};

#include "Point2D-inl.h" 