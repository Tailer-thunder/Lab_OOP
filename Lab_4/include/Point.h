#ifndef POINT_H
#define POINT_H

#include <concepts>
#include <iostream>


template<typename T>
concept Scalar = std::is_arithmetic_v<T>;


template <Scalar T>
class Point {
public:
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}

    void print() const {
        std::cout << "(" << x << ", " << y << ")";
    }
};

#endif // POINT_H
