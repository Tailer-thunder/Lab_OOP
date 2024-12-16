#include "../include/Rectangle.h"
#include "../include/Point.h"

template <Scalar T>
Rectangle<T>::Rectangle(Point<T> a, Point<T> b)
    : p1(std::make_shared<Point<T>>(a)), p2(std::make_shared<Point<T>>(b)) {}

template <Scalar T>
Rectangle<T>::Rectangle(const Rectangle<T>& other)
    : p1(other.p1), p2(other.p2) {} 

template <Scalar T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle<T>& other) {
    if (this != &other) {
        p1 = other.p1; 
        p2 = other.p2;
    }
    return *this;
}

template <Scalar T>
Rectangle<T>::Rectangle(Rectangle<T>&& other) noexcept
    : p1(std::move(other.p1)), p2(std::move(other.p2)) {}

template <Scalar T>
Rectangle<T>& Rectangle<T>::operator=(Rectangle<T>&& other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
    }
    return *this;
}

template <Scalar T>
T Rectangle<T>::area() const {
    return (p2->x - p1->x) * (p2->y - p1->y);
}

template <Scalar T>
Point<T> Rectangle<T>::center() const {
    return Point<T>((p1->x + p2->x) / 2, (p1->y + p2->y) / 2);
}

template <Scalar T>
void Rectangle<T>::print() const {
    std::cout << "Rectangle from ";
    std::cout << "(" << p1->x << ", " << p1->y << ") ";
    std::cout << "to ";
    std::cout << "(" << p2->x << ", " << p2->y << ") ";
    std::cout << "with Area: " << area() << std::endl;
}


template class Rectangle<double>;
template class Rectangle<int>;
template class Rectangle<float>;
