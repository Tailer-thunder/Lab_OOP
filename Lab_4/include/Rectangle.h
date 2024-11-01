#ifndef RECTANGLE
#define RECTANGLE

#include "Figure.h"
#include <iostream>
#include <memory>

template <Scalar T>
class Rectangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>> p1, p2;

public:
    Rectangle(Point<T> a = Point<T>(), Point<T> b = Point<T>()) 
        : p1(std::make_unique<Point<T>>(a)), p2(std::make_unique<Point<T>>(b)) {}

    Rectangle(const Rectangle<T>& other) 
        : p1(std::make_unique<Point<T>>(*other.p1)), p2(std::make_unique<Point<T>>(*other.p2)) {}

    Rectangle(Rectangle<T>&& other) noexcept 
        : p1(std::move(other.p1)), p2(std::move(other.p2)) {}

    Rectangle<T>& operator=(const Rectangle<T>& other) {
        if (this != &other) {
            p1 = std::make_unique<Point<T>>(*other.p1);
            p2 = std::make_unique<Point<T>>(*other.p2);
        }
        return *this;
    }

    Rectangle<T>& operator=(Rectangle<T>&& other) noexcept {
        if (this != &other) {
            p1 = std::move(other.p1);
            p2 = std::move(other.p2);
        }
        return *this;
    }

    T area() const override;
    Point<T> center() const override;
    void print() const override;
    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Rectangle<T>>(*this);
    }

    friend std::istream &operator>>(std::istream &stream, Rectangle<T> *obj) {
        Point<T> a, b;
        if (stream >> a.x >> a.y >> b.x >> b.y) {
            obj->p1 = std::make_unique<Point<T>>(a);
            obj->p2 = std::make_unique<Point<T>>(b);
        } else {
            stream.setstate(std::ios::failbit); 
        }
        return stream;
    }
};

#endif
