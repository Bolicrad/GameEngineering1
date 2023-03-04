#pragma once
template <typename T>
inline Point2D<T> operator*(int lhs, Point2D<T> rhs) {
	return rhs * lhs;
}