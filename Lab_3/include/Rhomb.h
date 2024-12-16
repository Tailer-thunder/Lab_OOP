#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"

class Rhomb : public Figure {
private:
    Point vertices[4];

public:
    Rhomb() = default;

    Point center() const override;
    explicit operator double() const override;

    Rhomb& operator=(const Rhomb& other);
    Rhomb& operator=(Rhomb&& other) noexcept;

    bool operator==(const Rhomb& other) const;
    bool operator!=(const Rhomb& other) const;

protected:
    std::ostream &print(std::ostream &stream) const override;
    std::istream &read(std::istream &stream) override;
};

#endif // RHOMB_H
