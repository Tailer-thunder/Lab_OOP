#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <utility>
#include <iostream>


template <class T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t capacity;
    size_t size;

    void resize(size_t newCapacity) {
        std::shared_ptr<T[]> newData(new T[newCapacity], std::default_delete<T[]>());
        for (size_t i = 0; i < size; ++i) {
            newData[i] = std::move(data[i]);
        }
        data = std::move(newData);
        capacity = newCapacity;
    }

public:
    Array(size_t initialCapacity = 10)
        : data(new T[initialCapacity], std::default_delete<T[]>()), capacity(initialCapacity), size(0) {}

    void add(const T& value) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        data[size++] = value;
    }

    void remove(size_t index) {
        if (index < size) {
            for (size_t i = index; i < size - 1; ++i) {
                data[i] = std::move(data[i + 1]);
            }
            --size;
        }
    }

    T& operator[](size_t index) const {
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << "Element " << i << ": ";
            data[i]->print();
            std::cout << std::endl;
        }
    }
};

#endif 