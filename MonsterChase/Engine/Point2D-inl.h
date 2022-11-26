#pragma once

//equality
inline bool Point2D::operator== (const Point2D& rhs) const {
	return x == rhs.getX() && y == rhs.getY();
}

//inequality
inline bool Point2D::operator!= (const Point2D& rhs) const{
	return !(*this == rhs);
}

//Point2D + Point2D
inline const Point2D Point2D::operator+(const Point2D& rhs) const{
	return Point2D(x + rhs.getX(), y + rhs.getY());
}

//negate
inline const Point2D Point2D::operator-() const {
	return Point2D(-x, -y);
}

//Point2D - Point2D
inline const Point2D Point2D::operator-(const Point2D& rhs) const {
	return Point2D(x - rhs.getX(), y - rhs.getY());
}

//Point2D * int
inline const Point2D Point2D::operator*(int rhs) const {
	return Point2D(x * rhs, y * rhs);
}

//Point2D / int
inline const Point2D Point2D::operator/(int rhs) const {
	return Point2D(x / rhs, y / rhs);
}

//Direct Assignment
inline Point2D& Point2D::operator=(const Point2D& rhs) {
	x = rhs.getX();
	y = rhs.getY();
	return *this;
}

//Point2D += Point2D
inline Point2D& Point2D::operator+=(const Point2D& rhs) {
	x += rhs.getX();
	y += rhs.getY();
	return *this;
}

//Point2D -= Point2D
inline Point2D& Point2D::operator-=(const Point2D& rhs) {
	x -= rhs.getX();
	y -= rhs.getY();
	return *this;
}

//Point2D *= int
inline Point2D& Point2D::operator*=(int rhs) {
	*this = *this * rhs;
	return *this;
}

//Point2D /= int
inline Point2D& Point2D::operator/=(int rhs) {
	*this = *this / rhs;
	return *this;
}

inline Point2D operator*(int lhs, Point2D rhs) {
	return rhs * lhs; 
}