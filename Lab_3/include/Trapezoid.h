#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"

class Trapezoid : public Figure {
private:
    Point vertices[4];

public:
    Trapezoid() = default;

    Point center() const override;
    explicit operator double() const override;

    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;

    bool operator==(const Trapezoid& other) const;
    bool operator!=(const Trapezoid& other) const;

protected:
    std::ostream &print(std::ostream &stream) const override;
    std::istream &read(std::istream &stream) override;
};

#endif // TRAPEZOID_H
