#include "../include/Trapezoid.h"
#include "../include/Point.h"

template <Scalar T>
Trapezoid<T>::Trapezoid(Point<T> a, Point<T> b, Point<T> c, Point<T> d)
    : p1(std::make_shared<Point<T>>(a)), p2(std::make_shared<Point<T>>(b)),
      p3(std::make_shared<Point<T>>(c)), p4(std::make_shared<Point<T>>(d)) {}

template <Scalar T>
Trapezoid<T>::Trapezoid(const Trapezoid<T>& other)
    : p1(other.p1), p2(other.p2), p3(other.p3), p4(other.p4) {} /

template <Scalar T>
Trapezoid<T>& Trapezoid<T>::operator=(const Trapezoid<T>& other) {
    if (this != &other) {
        p1 = other.p1; 
        p2 = other.p2;
        p3 = other.p3;
        p4 = other.p4;
    }
    return *this;
}

template <Scalar T>
Trapezoid<T>::Trapezoid(Trapezoid<T>&& other) noexcept
    : p1(std::move(other.p1)), p2(std::move(other.p2)), p3(std::move(other.p3)), p4(std::move(other.p4)) {}

template <Scalar T>
Trapezoid<T>& Trapezoid<T>::operator=(Trapezoid<T>&& other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
        p4 = std::move(other.p4);
    }
    return *this;
}

template <Scalar T>
T Trapezoid<T>::area() const {
    T base1 = std::abs(p1->y - p2->y);
    T base2 = std::abs(p3->y - p4->y);
    T height = std::abs(p1->x - p3->x); 
    return 0.5 * (base1 + base2) * height;
}

template <Scalar T>
Point<T> Trapezoid<T>::center() const {
    return Point<T>((p1->x + p3->x) / 2, (p1->y + p3->y) / 2);
}

template <Scalar T>
void Trapezoid<T>::print() const {
    std::cout << "Trapezoid: ";
    p1->print(); std::cout << ", ";
    p2->print(); std::cout << ", ";
    p3->print(); std::cout << ", ";
    p4->print(); std::cout << " Area: " << area() << std::endl;
}


template class Trapezoid<double>;
template class Trapezoid<int>;
template class Trapezoid<float>;