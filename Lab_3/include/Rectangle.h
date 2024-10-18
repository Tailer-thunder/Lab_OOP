#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"

class Rectangle : public Figure {
private:
    Point vertices[4];

public:
    Rectangle() = default;

    Point center() const override;
    explicit operator double() const override;

    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;

    bool operator==(const Rectangle& other) const;
    bool operator!=(const Rectangle& other) const;

protected:
    std::ostream &print(std::ostream &stream) const override;
    std::istream &read(std::istream &stream) override;
};

#endif // RECTANGLE_H
