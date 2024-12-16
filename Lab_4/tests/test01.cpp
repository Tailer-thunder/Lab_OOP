#include <gtest/gtest.h>
#include "../include/Rectangle.h"
#include "../include/Rhomb.h"
#include "../include/Trapezoid.h"
#include <sstream>

template <typename T>
class FigureTest : public ::testing::Test {};

using TestTypes = ::testing::Types<int, double>;
TYPED_TEST_SUITE(FigureTest, TestTypes);

TYPED_TEST(FigureTest, RectangleAreaTest) {
    Rectangle<TypeParam> rect(Point<TypeParam>(0, 0), Point<TypeParam>(4, 3));
    EXPECT_NEAR(rect.area(), 12, 1e-9); 
}

TYPED_TEST(FigureTest, RectangleCenterTest) {
    Rectangle<TypeParam> rect(Point<TypeParam>(0, 0), Point<TypeParam>(4, 4));
    Point<TypeParam> center = rect.center();
    EXPECT_NEAR(center.x, 2, 1e-9);
    EXPECT_NEAR(center.y, 2, 1e-9);
}

TYPED_TEST(FigureTest, TrapezoidAreaTest) {
    Trapezoid<TypeParam> trap(Point<TypeParam>(0, 0), Point<TypeParam>(2, 0),
                              Point<TypeParam>(3, 2), Point<TypeParam>(1, 2));
    EXPECT_NEAR(trap.area(), 4, 1e-9);
}

TYPED_TEST(FigureTest, TrapezoidCenterTest) {
    Trapezoid<TypeParam> trap(Point<TypeParam>(0, 0), Point<TypeParam>(2, 0),
                              Point<TypeParam>(3, 2), Point<TypeParam>(1, 2));
    Point<TypeParam> center = trap.center();
    EXPECT_NEAR(center.x, 1.5, 1e-9);
    EXPECT_NEAR(center.y, 1, 1e-9);
}

TYPED_TEST(FigureTest, RhombusAreaTest) {
    Rhombus<TypeParam> rhombus(Point<TypeParam>(0, 0), Point<TypeParam>(2, 1),
                                Point<TypeParam>(1, 2), Point<TypeParam>(-1, 1));
    EXPECT_NEAR(rhombus.area(), 2, 1e-9);
}

TYPED_TEST(FigureTest, RhombusCenterTest) {
    Rhombus<TypeParam> rhombus(Point<TypeParam>(0, 0), Point<TypeParam>(2, 1),
                                Point<TypeParam>(1, 2), Point<TypeParam>(-1, 1));
    Point<TypeParam> center = rhombus.center();
    EXPECT_NEAR(center.x, 0, 1e-9);
    EXPECT_NEAR(center.y, 1, 1e-9);
}

// Тест на исключение для ромба
TYPED_TEST(FigureTest, InvalidRhombusTest) {
    EXPECT_THROW(Rhombus<TypeParam>(Point<TypeParam>(0, 0), Point<TypeParam>(1, 1), 
                                     Point<TypeParam>(2, 0), Point<TypeParam>(1, -1)), 
                 std::invalid_argument);
}

// Основная функция тестирования
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
