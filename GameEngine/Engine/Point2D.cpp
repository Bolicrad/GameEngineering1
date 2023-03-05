#include "Point2D.h"

template <typename T>
const Point2D<T> Point2D<T>::zero = Point2D<T>(T(0), T(0));

template <typename T>
const Point2D<T> Point2D<T>::one = Point2D<T>(T(1), T(1));

template <typename T>
const Point2D<T> Point2D<T>::left = Point2D<T>(T(-1), T(0));

template <typename T>
const Point2D<T> Point2D<T>::right = Point2D<T>(T(1), T(0));

template <typename T>
const Point2D<T> Point2D<T>::up = Point2D<T>(T(0), T(1));

template <typename T>
const Point2D<T> Point2D<T>::down = Point2D<T>(T(0), T(-1));

template class Point2D<int>;
template class Point2D<float>;