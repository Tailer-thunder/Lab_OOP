#include "../include/Rectangle.h"
#include <cmath>
#include <iostream>


Figure::Point Rectangle::center() const {
    Point center{};
    for (const auto& vertex : vertices) {
        center.x += vertex.x;
        center.y += vertex.y;
    }
    center.x /= 4;  
    center.y /= 4;  
    return center;
}


Rectangle::operator double() const {
    double side1 = Figure::distance(vertices[0], vertices[1]); 
    double side2 = Figure::distance(vertices[1], vertices[2]);  
    return side1 * side2;  
}


std::ostream &Rectangle::print(std::ostream &stream) const {
    stream << "Прямоугольник с координатами: ";
    for (const auto& vertex : vertices) {
        stream << "(" << vertex.x << "," << vertex.y << ") ";
    }
    return stream;
}


std::istream &Rectangle::read(std::istream &stream) {
    for (auto& vertex : vertices) {
        stream >> vertex.x >> vertex.y;
    }
    return stream;
}


Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}


Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }
    return *this;
}


bool Rectangle::operator==(const Rectangle& other) const {
    for (int i = 0; i < 4; ++i) {
        if (vertices[i].x != other.vertices[i].x || vertices[i].y != other.vertices[i].y) {
            return false;
        }
    }
    return true;
}


bool Rectangle::operator!=(const Rectangle& other) const {
    return !(*this == other);
}