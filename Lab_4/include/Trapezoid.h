#ifndef TRAPEZOID
#define TRAPEZOID

#include "figure.h"
#include <array>

template <Scalar T>
class Trapezoid : public Figure<T> {
private:
    std::array<Point<T>, 4> points;

    bool areParallel(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) const {
        T deltaX1 = p2.x - p1.x;
        T deltaY1 = p2.y - p1.y;
        T deltaX2 = p4.x - p3.x;
        T deltaY2 = p4.y - p3.y;

        return (deltaX1 * deltaY2) == (deltaY1 * deltaX2);
    }

    bool isValidTrapezoid() const {
        return areParallel(points[0], points[1], points[2], points[3]) || 
               areParallel(points[0], points[3], points[1], points[2]);
    }

public:
    Trapezoid(Point<T> a = Point<T>(), Point<T> b = Point<T>(), Point<T> c = Point<T>(), Point<T> d = Point<T>()) 
        : points{{a, b, c, d}} {
        if (!isValidTrapezoid()) {
            throw std::invalid_argument("Введенные точки не образуют трапецию");
        }
    }

    Trapezoid(const Trapezoid<T>& other) = default;
    Trapezoid<T>& operator=(const Trapezoid<T>& other) = default;

    T area() const override;
    Point<T> center() const override;
    void print() const override;

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Trapezoid<T>>(*this);
    }

    friend std::istream& operator>>(std::istream& stream, Trapezoid<T>* obj) {
        Point<T> a, b, c, d;
        if (!(stream >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y)) {
            throw std::invalid_argument("Некорректный ввод для Trapezoid");
        }

        obj->points = {a, b, c, d};

        if (!obj->isValidTrapezoid()) {
            throw std::invalid_argument("Введенные точки не образуют трапецию");
        }

        return stream;
    }
};

#endif // TRAPEZOID
