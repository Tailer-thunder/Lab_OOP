#include <gtest/gtest.h>
#include <memory_resource>
#include "../include/dynamic_array.hpp"
#include "../include/memory_resource.hpp"


TEST(DynamicArrayTests, PushBackAndAccess_Int) {
    constexpr size_t bufferSize = 1024;
    std::byte buffer[bufferSize];
    std::pmr::monotonic_buffer_resource memoryResource(buffer, bufferSize);

    DynamicArray<int> array(&memoryResource);


    array.push_back(10);
    array.push_back(20);
    array.push_back(30);

    ASSERT_EQ(array.size(), 3);
    EXPECT_EQ(array[0], 10);
    EXPECT_EQ(array[1], 20);
    EXPECT_EQ(array[2], 30);
}


struct ComplexType {
    int id;
    std::string name;

    ComplexType(int i, const std::string& n) : id(i), name(n) {}

    bool operator==(const ComplexType& other) const {
        return id == other.id && name == other.name;
    }
};

TEST(DynamicArrayTests, PushBackAndAccess_ComplexType) {
    constexpr size_t bufferSize = 1024;
    std::byte buffer[bufferSize];
    std::pmr::monotonic_buffer_resource memoryResource(buffer, bufferSize);

    DynamicArray<ComplexType> array(&memoryResource);


    array.push_back({1, "Alice"});
    array.push_back({2, "Bob"});

    ASSERT_EQ(array.size(), 2);
    EXPECT_EQ(array[0], ComplexType(1, "Alice"));
    EXPECT_EQ(array[1], ComplexType(2, "Bob"));
}


TEST(DynamicArrayTests, Iterators_Int) {
    constexpr size_t bufferSize = 1024;
    std::byte buffer[bufferSize];
    std::pmr::monotonic_buffer_resource memoryResource(buffer, bufferSize);

    DynamicArray<int> array(&memoryResource);

    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    auto it = array.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, array.end());
}


TEST(DynamicArrayTests, CustomMemoryResource) {
    constexpr size_t bufferSize = 1024;
    std::byte buffer[bufferSize];
    std::pmr::monotonic_buffer_resource memoryResource(buffer, bufferSize);

    DynamicArray<int> array(&memoryResource);

    array.push_back(5);
    array.push_back(15);

    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[0], 5);
    EXPECT_EQ(array[1], 15);
}
