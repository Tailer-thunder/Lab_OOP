#include "dynamic_array.h"

template <typename T>
DynamicArray<T>::DynamicArray(size_t capacity)
    : size_(0), capacity_(capacity) {
    data_ = allocator_.allocate(capacity_);
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    for (size_t i = 0; i < size_; ++i) {
        allocator_.destroy(&data_[i]);
    }
    allocator_.deallocate(data_, capacity_);
}

template <typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        reallocate(capacity_ * 2);
    }
    allocator_.construct(&data_[size_], value);
    ++size_;
}

template <typename T>
T& DynamicArray<T>::operator[](size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <typename T>
size_t DynamicArray<T>::size() const {
    return size_;
}

template <typename T>
size_t DynamicArray<T>::capacity() const {
    return capacity_;
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::begin() {
    return Iterator(data_);
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::end() {
    return Iterator(data_ + size_);
}

template <typename T>
void DynamicArray<T>::reallocate(size_t new_capacity) {
    T* new_data = allocator_.allocate(new_capacity);
    for (size_t i = 0; i < size_; ++i) {
        allocator_.construct(&new_data[i], std::move(data_[i]));
        allocator_.destroy(&data_[i]);
    }
    allocator_.deallocate(data_, capacity_);
    data_ = new_data;
    capacity_ = new_capacity;
}
