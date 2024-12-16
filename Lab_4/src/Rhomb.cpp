#include "../include/Rhomb.h"
#include "../include/Point.h"

template <Scalar T>
Rhomb<T>::Rhomb(Point<T> a, Point<T> b, Point<T> c, Point<T> d) {
    if (!isValidRhomb(a, b, c, d)) {
        throw std::invalid_argument("Введённые точки не образуют ромб");
    }
    p1 = std::make_shared<Point<T>>(a);
    p2 = std::make_shared<Point<T>>(b);
    p3 = std::make_shared<Point<T>>(c);
    p4 = std::make_shared<Point<T>>(d);
}

template <Scalar T>
Rhomb<T>::Rhomb(const Rhomb<T>& other)
    : p1(other.p1), p2(other.p2), p3(other.p3), p4(other.p4) {} // Копируем указатели

template <Scalar T>
Rhomb<T>& Rhomb<T>::operator=(const Rhomb<T>& other) {
    if (this != &other) {
        p1 = other.p1; // Просто копируем указатели
        p2 = other.p2;
        p3 = other.p3;
        p4 = other.p4;
    }
    return *this;
}

template <Scalar T>
Rhomb<T>::Rhomb(Rhomb<T>&& other) noexcept
    : p1(std::move(other.p1)), p2(std::move(other.p2)), p3(std::move(other.p3)), p4(std::move(other.p4)) {}

template <Scalar T>
Rhomb<T>& Rhomb<T>::operator=(Rhomb<T>&& other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
        p4 = std::move(other.p4);
    }
    return *this;
}

template <Scalar T>
T Rhomb<T>::area() const {
    return ((p1->y - p3->y) * (p2->x - p4->x)) / 2;
}

template <Scalar T>
Point<T> Rhomb<T>::center() const {
    return Point<T>((p1->x + p3->x) / 2, (p1->y + p3->y) / 2);
}

template <Scalar T>
void Rhomb<T>::print() const {
    std::cout << "Rhomb: ";
    p1->print(); std::cout << ", ";
    p2->print(); std::cout << ", ";
    p3->print(); std::cout << ", ";
    p4->print(); std::cout << " Area: " << area() << std::endl;
}

template class Rhomb<double>;
template class Rhomb<int>;
template class Rhomb<float>;
