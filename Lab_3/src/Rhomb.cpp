#include "../include/Rhomb.h"

#include <cmath>
#include <iostream>


Figure::Point Rhomb::center() const {
    Point center{};
    for (const auto& vertex : vertices) {
        center.x += vertex.x;
        center.y += vertex.y;
    }
    center.x /= 4; 
    center.y /= 4;  
    return center;
}


Rhomb::operator double() const {
    double diagonal1 = Figure::distance(vertices[0], vertices[2]);  
    double diagonal2 = Figure::distance(vertices[1], vertices[3]);  
    return 0.5 * diagonal1 * diagonal2; 
}


std::ostream &Rhomb::print(std::ostream &stream) const {
    stream << "Ромб с координатами: ";
    for (const auto& vertex : vertices) {
        stream << "(" << vertex.x << "," << vertex.y << ") ";
    }
    return stream;
}


std::istream &Rhomb::read(std::istream &stream) {
    for (auto& vertex : vertices) {
        stream >> vertex.x >> vertex.y;
    }
    return stream;
}


Rhomb& Rhomb::operator=(const Rhomb& other) {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}


Rhomb& Rhomb::operator=(Rhomb&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }
    return *this;
}

bool Rhomb::operator==(const Rhomb& other) const {
    for (int i = 0; i < 4; ++i) {
        if (vertices[i].x != other.vertices[i].x || vertices[i].y != other.vertices[i].y) {
            return false;
        }
    }
    return true;
}


bool Rhomb::operator!=(const Rhomb& other) const {
    return !(*this == other);
}
