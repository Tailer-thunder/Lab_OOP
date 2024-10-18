#include <gtest/gtest.h>
#include "../include/Rectangle.h"
#include "../include/Rhomb.h"
#include "../include/Trapezoid.h"

TEST(RectangleTests, AssignmentOperator) {
    Rectangle* a = new Rectangle();
    Rectangle* b = new Rectangle();
    *b = *a;
    ASSERT_TRUE(*a == *b);
    delete a;
    delete b;
}

TEST(RectangleTests, EqualityOperator) {
    Rectangle a;
    Rectangle b;
    ASSERT_TRUE(a == b);
}

TEST(RhombTests, AssignmentOperator) {
    Rhomb* a = new Rhomb();
    Rhomb* b = new Rhomb();
    *b = *a;
    ASSERT_TRUE(*a == *b);
    delete a;
    delete b;
}

TEST(RhombTests, EqualityOperator) {
    Rhomb a;
    Rhomb b;
    ASSERT_TRUE(a == b);
}

TEST(TrapezoidTests, AssignmentOperator) {
    Trapezoid* a = new Trapezoid();
    Trapezoid* b = new Trapezoid();
    *b = *a;
    ASSERT_TRUE(*a == *b);
    delete a;
    delete b;
}

TEST(TrapezoidTests, EqualityOperator) {
    Trapezoid a;
    Trapezoid b;
    ASSERT_TRUE(a == b);
}

TEST(RectangleTests, AreaCalculation) {
    Rectangle rect;
    ASSERT_DOUBLE_EQ(static_cast<double>(rect), 0.0); 
}

TEST(RhombTests, AreaCalculation) {
    Rhomb rhomb;
    ASSERT_DOUBLE_EQ(static_cast<double>(rhomb), 0.0); 
}

TEST(TrapezoidTests, AreaCalculation) {
    Trapezoid trap;
    ASSERT_DOUBLE_EQ(static_cast<double>(trap), 0.0); 
}
