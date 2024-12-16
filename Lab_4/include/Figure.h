#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include <memory>
#include <iostream>


template <Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    virtual T area() const = 0;
    virtual void print() const = 0;
    virtual Point<T> center() const = 0;

    virtual std::shared_ptr<Figure<T>> clone() const = 0;

    operator double() const {
        return area();
    }

    bool operator<(const Figure<T>& other) const {
        return area() < other.area();
    }

    bool operator>(const Figure<T>& other) const {
        return area() > other.area();
    }

    friend std::ostream &operator<<(std::ostream &stream, const Figure<T> *obj) {
        obj->print();
        return stream;
    }

    friend std::istream &operator>>(std::istream &stream, Figure<T> *obj) {
        return stream;
    }
};


#endif // FIGURE_H
