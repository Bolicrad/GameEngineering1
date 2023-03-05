#include "Point2D.h"

template <typename T>
const Point2D<T> Point2D<T>::zero = Point2D<T>(T(0), T(0));

template class Point2D<int>;
template class Point2D<float>;