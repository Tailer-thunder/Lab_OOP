#include <iostream>
#include <memory_resource>
#include "../include/dynamic_array.h"
#include "../include/memory_resource.h"

struct ComplexType {
    int id;
    std::string name;

    ComplexType(int i, const std::string& n) : id(i), name(n) {}
};

int main() {
    constexpr size_t bufferSize = 1024;
    std::byte buffer[bufferSize];
    std::pmr::monotonic_buffer_resource memoryResource(buffer, bufferSize);

    DynamicArray<int> intArray(&memoryResource);
    DynamicArray<ComplexType> complexArray(&memoryResource);

    std::cout << "Добавляем элементы в intArray:" << std::endl;
    intArray.push_back(1);
    intArray.push_back(2);
    intArray.push_back(3);

    for (const auto& elem : intArray) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "Добавляем элементы в complexArray:" << std::endl;
    complexArray.push_back({1, "Alice"});
    complexArray.push_back({2, "Bob"});

    for (const auto& elem : complexArray) {
        std::cout << "ID: " << elem.id << ", Name: " << elem.name << std::endl;
    }

    return 0;
}
