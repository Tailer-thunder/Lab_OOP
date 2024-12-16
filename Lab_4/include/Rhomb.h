#ifndef RHOMB
#define RHOMB

#include "Figure.h"
#include <array>
#include <stdexcept>
#include <cmath>

template <Scalar T>
class Rhomb : public Figure<T> {
private:
    std::array<Point<T>, 4> points;

    T distance(const Point<T>& p1, const Point<T>& p2) const {
        return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }

    bool isValidRhomb() const {
        T d1 = distance(points[0], points[1]);
        T d2 = distance(points[1], points[2]);
        T d3 = distance(points[2], points[3]);
        T d4 = distance(points[3], points[0]);

        return (d1 == d3 && d2 == d4 && d1 == d2);
    }

public:
    Rhomb(Point<T> a = Point<T>(), Point<T> b = Point<T>(), Point<T> c = Point<T>(), Point<T> d = Point<T>()) 
        : points{a, b, c, d} {
        if (!isValidRhomb()) {
            throw std::invalid_argument("Указанные точки не образуют ромб");
        }
    }

    Rhomb(const Rhombus<T>& other) = default;
    Rhomb<T>& operator=(const Rhombus<T>& other) = default;

    T area() const override;
    Point<T> center() const override;
    void print() const override;

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Rhombus<T>>(*this);
    }

    friend std::istream &operator>>(std::istream &stream, Rhombus<T> *obj) {
        for (auto& point : obj->points) {
            if (!(stream >> point.x >> point.y)) {
                throw std::invalid_argument("Некорректный ввод для Rhombus");
            }
        }

        if (!obj->isValidRhomb()) {
            throw std::invalid_argument("Введенные точки не образуют ромб");
        }

        return stream;
    }
};

#endif // RHOMB
