#include <gtest/gtest.h>
#include "../include/closest_pair_tonum.h"

TEST(test_01, basic_test_set) {
    int upper_limit = 50;
    std::string expected_output = "(45, 36)";
    std::string actual_output = closest_pair_tonum(upper_limit);
    ASSERT_TRUE(actual_output == expected_output);
}

TEST(test_02, basic_test_set) {
    int upper_limit = 30;
    std::string expected_output = "(29, 20)";
    std::string actual_output = closest_pair_tonum(upper_limit);
    ASSERT_TRUE(actual_output == expected_output);
}

TEST(test_03, basic_test_set) {
    int upper_limit = 10;
    std::string expected_output = "(5, 4)";
    std::string actual_output = closest_pair_tonum(upper_limit);
    ASSERT_TRUE(actual_output == expected_output);
}

TEST(test_04, basic_test_set) {
    int upper_limit = 15;
    std::string expected_output = "(13, 12)";
    std::string actual_output = closest_pair_tonum(upper_limit);
    ASSERT_TRUE(actual_output == expected_output);
}

TEST(test_05, basic_test_set) {
    int upper_limit = 20;
    std::string expected_output = "(17, 8)";
    std::string actual_output = closest_pair_tonum(upper_limit);
    ASSERT_TRUE(actual_output == expected_output);
}