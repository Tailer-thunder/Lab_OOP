#include <gtest/gtest.h>
#include "../include/Thirteen.hpp"


TEST(test_01, basic_initialization_test) {
    Thirteen var1 = Thirteen();
    Thirteen var2 = Thirteen(3, 'C');
    Thirteen var3 = Thirteen{'1', 'A', 'C'};
    Thirteen var4 = Thirteen("1A7");
    Thirteen var5 = var1;
    ASSERT_TRUE(true);
}

TEST(test_02, comparison_test) {
    Thirteen var1 = Thirteen("111");
    Thirteen var2 = Thirteen("CCC");
    Thirteen var3 = var1;

    ASSERT_TRUE(var1 == var3);
    ASSERT_FALSE(var1 != var3);

    ASSERT_FALSE(var1 > var2);
    ASSERT_TRUE(var2 > var1);

    ASSERT_TRUE(var1 < var2);
    ASSERT_FALSE(var2 < var1);
}

TEST(test_03, addition_subtraction_test) {
    Thirteen var1 = Thirteen("C2");
    Thirteen res1 = Thirteen("C3");
    Thirteen res2 = Thirteen("B1");

    var1 += Thirteen("1");
    ASSERT_TRUE(var1 == res1);

    var1 -= Thirteen("12");
    ASSERT_TRUE(var1 == res2);
}

TEST(test_04, copy_move_constructor_test) {
    Thirteen var1 = Thirteen("1A7");
    Thirteen var2 = var1;
    Thirteen var3 = std::move(var1);

    ASSERT_TRUE(var2 == Thirteen("1A7"));
    ASSERT_TRUE(var3 == Thirteen("1A7"));
    ASSERT_TRUE(var1 == Thirteen()); 
}

TEST(test_05, exception_handling_test) {
    Thirteen var1 = Thirteen("1A7");
    try {
        var1 -= Thirteen("1B0"); 
        FAIL() << "Ожидалось исключение std::logic_error";
    } catch (const std::logic_error& e) {
        ASSERT_STREQ("Разность не может быть отрицательной", e.what());
    } catch (...) {
        FAIL() << "Ожидалось исключение std::logic_error";
    }
}

TEST(test_06, addition_with_carry_test) {
    Thirteen var1 = Thirteen("C");
    Thirteen var2 = Thirteen("1");
    Thirteen res = Thirteen("10");

    var1 += var2;
    ASSERT_TRUE(var1 == res);
}

TEST(test_07, subtraction_with_borrow_test) {
    Thirteen var1 = Thirteen("1A");
    Thirteen var2 = Thirteen("B");
    Thirteen res = Thirteen("F");

    var1 -= var2;
    ASSERT_TRUE(var1 == res);
}

TEST(test_08, complex_operations_test) {
    Thirteen var1 = Thirteen("2A4");
    Thirteen var2 = Thirteen("1C1");

    var1 += var2;
    Thirteen res_add = Thirteen("4A5");
    ASSERT_TRUE(var1 == res_add);

    var1 -= Thirteen("1B5");
    Thirteen res_sub = Thirteen("310");
    ASSERT_TRUE(var1 == res_sub);
}

TEST(test_09, zero_initialization_test) {
    Thirteen var1 = Thirteen("0000");
    Thirteen var2 = Thirteen();
    ASSERT_TRUE(var1 == var2);
}