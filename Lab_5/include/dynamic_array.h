#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cstddef>  // Для size_t
#include <stdexcept> // Для std::out_of_range

template <typename T>
class DynamicArray {
public:
    // Конструктор
    DynamicArray(size_t size = 0);
    // Деструктор
    ~DynamicArray();

    // Добавить элемент в конец
    void push_back(const T& value);
    // Получить доступ к элементу по индексу
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // Получить размер массива
    size_t size() const;
    // Получить ёмкость массива
    size_t capacity() const;

    // Итератор для начала
    class Iterator {
    public:
        Iterator(T* ptr) : ptr(ptr) {}
        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    private:
        T* ptr;
    };

    Iterator begin();
    Iterator end();

private:
    T* data;             // Массив данных
    size_t current_size; // Текущий размер
    size_t current_capacity; // Текущая ёмкость

    // Перераспределить память
    void reallocate(size_t new_size);
};

// Реализация

template <typename T>
DynamicArray<T>::DynamicArray(size_t size) 
    : current_size(size), current_capacity(size) {
    data = (size > 0) ? new T[size] : nullptr;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (current_size == current_capacity) {
        reallocate(current_capacity == 0 ? 1 : current_capacity * 2);
    }
    data[current_size++] = value;
}

template <typename T>
T& DynamicArray<T>::operator[](size_t index) {
    if (index >= current_size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const T& DynamicArray<T>::operator[](size_t index) const {
    if (index >= current_size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
size_t DynamicArray<T>::size() const {
    return current_size;
}

template <typename T>
size_t DynamicArray<T>::capacity() const {
    return current_capacity;
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::begin() {
    return Iterator(data);
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::end() {
    return Iterator(data + current_size);
}

template <typename T>
void DynamicArray<T>::reallocate(size_t new_size) {
    T* new_data = new T[new_size];
    for (size_t i = 0; i < current_size; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    current_capacity = new_size;
}

#endif // DYNAMIC_ARRAY_H
