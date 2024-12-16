#include <gtest/gtest.h>
#include "../include/Thirteen.hpp"


TEST(ThirteenTest, ConstructorsAndInitialization) {
    Thirteen var1; 
    Thirteen var2(3, '7');  
    Thirteen var3{'1', '2', '3'};  
    Thirteen var4("107");  

  
    ASSERT_EQ(var1, Thirteen());  
    ASSERT_EQ(var2, Thirteen(3, '7'));  
    ASSERT_EQ(var3, Thirteen({'1', '2', '3'}));  
    ASSERT_EQ(var4, Thirteen("107"));
}


TEST(ThirteenTest, ComparisonOperators) {
    Thirteen var1("111");
    Thirteen var2("777");
    Thirteen var3 = var1;

    ASSERT_TRUE(var1 == var3);  
    ASSERT_FALSE(var1 != var3);  
    ASSERT_TRUE(var2 > var1);  
    ASSERT_TRUE(var1 < var2);  
}


TEST(ThirteenTest, AdditionOperator) {
    Thirteen var1("777");
    Thirteen expected_result("1000");

    var1 += Thirteen("1");
    ASSERT_EQ(var1, expected_result);  

    
    Thirteen var2("A2");
    Thirteen var3("3");
    Thirteen expected_result2("A5");

    var2 += var3;
    ASSERT_EQ(var2, expected_result2);  


    Thirteen var4("C12");
    Thirteen expected_result3("C13");

    var4 += Thirteen("1");
    ASSERT_EQ(var4, expected_result3);  
}


TEST(ThirteenTest, SubtractionOperator) {

    Thirteen var1("1000");
    Thirteen expected_result("777");

    var1 -= Thirteen("223");
    ASSERT_EQ(var1, expected_result); 


    Thirteen var2("A5");
    Thirteen var3("3");
    Thirteen expected_result2("A2");

    var2 -= var3;
    ASSERT_EQ(var2, expected_result2);  

    Thirteen var4("C13");
    Thirteen expected_result3("C12");

    var4 -= Thirteen("1");
    ASSERT_EQ(var4, expected_result3);  
}


TEST(ThirteenTest, AssignmentOperator) {
    Thirteen var1("123");
    Thirteen var2;

    var2 = var1;
    ASSERT_EQ(var2, var1); 
}


TEST(ThirteenTest, DestructorTest) {
    Thirteen* var1 = new Thirteen("123");
    delete var1;
    ASSERT_TRUE(true);  
}


TEST(ThirteenTest, CopyConstructor) {
    Thirteen var1("123");
    Thirteen var2 = var1;
    ASSERT_EQ(var2, var1);  
}


TEST(ThirteenTest, MoveConstructor) {
    Thirteen var1("123");
    Thirteen var2 = std::move(var1);

    ASSERT_EQ(var2, Thirteen("123"));  
}


TEST(ThirteenTest, PrintTest) {
    Thirteen var1("123");
    std::stringstream ss;
    var1.print(ss);

    ASSERT_EQ(ss.str(), "123"); 
}