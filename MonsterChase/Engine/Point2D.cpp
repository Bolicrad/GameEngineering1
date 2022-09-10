#pragma once
#include "Point2D.h"
//equality
bool Point2D::operator== (Point2D rhs) {
	return x == rhs.getX() && y == rhs.getY();
}

//inequality
bool Point2D::operator!= (Point2D rhs) {
    return !(*this == rhs);
}

//Point2D + Point2D
Point2D Point2D::operator+(Point2D rhs) {
	return Point2D(x + rhs.getX(), y + rhs.getY());
}

//negate
Point2D Point2D::operator-() {
	return Point2D(-x, -y);
}

//Point2D - Point2D
Point2D Point2D::operator-(Point2D rhs) {
	return *this + (- rhs);
}

//Point2D * int
Point2D Point2D::operator*(int rhs) {
	return Point2D(x * rhs, y * rhs);
}

//Point2D / int
Point2D Point2D::operator/(int rhs) {
	return Point2D(x / rhs, y / rhs);
}

//Direct Assignment
Point2D& Point2D::operator=(Point2D rhs) {
    x = rhs.getX();
    y = rhs.getY();
	return *this;
}

//Point2D += Point2D
Point2D& Point2D::operator+=(Point2D rhs) {
    *this = *this + rhs;
	return *this;
}

//Point2D -= Point2D
Point2D& Point2D::operator-=(Point2D rhs) {
    *this = *this - rhs;
	return *this;
}

//Point2D *= int
Point2D& Point2D::operator*=(int rhs) {
	*this = *this * rhs;
	return *this;
}

//Point2D /= int
Point2D& Point2D::operator/=(int rhs) {
	*this = *this / rhs;
	return *this;
}

Point2D Point2D::zero = Point2D(0,0);