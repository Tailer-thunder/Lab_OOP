#ifndef FIGURE_H
#define FIGURE_H

#include <string>
#include <cmath>
#include <iostream>

class Figure {
public:
    struct Point {
        double x;
        double y;
    };

    virtual Point center() const = 0;
    virtual explicit operator double() const = 0;

    friend std::ostream &operator<<(std::ostream &stream, Figure const *obj);
    friend std::istream &operator>>(std::istream &stream, Figure *obj);

    virtual ~Figure() = default;

protected:
    virtual std::ostream &print(std::ostream &stream) const = 0;
    virtual std::istream &read(std::istream &stream) = 0;

    static double distance(const Point& a, const Point& b) {
        return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    }
};

#endif // FIGURE_H
