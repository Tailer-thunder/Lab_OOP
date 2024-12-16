#include "../include/Trapezoid.h"
#include <cmath>
#include <iostream>

Figure::Point Trapezoid::center() const {
    Point center{};
    for (const auto& vertex : vertices) {
        center.x += vertex.x;
        center.y += vertex.y;
    }
    center.x /= 4;  
    center.y /= 4; 
    return center;
}

// Вычисление площади трапеции
Trapezoid::operator double() const {
    double a = Figure::distance(vertices[0], vertices[1]);  
    double b = Figure::distance(vertices[2], vertices[3]);  
    double height = std::abs(vertices[0].y - vertices[2].y);  
    return 0.5 * (a + b) * height; 
}


std::ostream &Trapezoid::print(std::ostream &stream) const {
    stream << "Трапеция с координатами: ";
    for (const auto& vertex : vertices) {
        stream << "(" << vertex.x << "," << vertex.y << ") ";
    }
    return stream;
}


std::istream &Trapezoid::read(std::istream &stream) {
    for (auto& vertex : vertices) {
        stream >> vertex.x >> vertex.y;
    }
    return stream;
}


Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}


Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }
    return *this;
}


bool Trapezoid::operator==(const Trapezoid& other) const {
    for (int i = 0; i < 4; ++i) {
        if (vertices[i].x != other.vertices[i].x || vertices[i].y != other.vertices[i].y) {
            return false;
        }
    }
    return true;
}


bool Trapezoid::operator!=(const Trapezoid& other) const {
    return !(*this == other);
}
