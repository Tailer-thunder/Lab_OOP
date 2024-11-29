#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <memory_resource>
#include <stdexcept>
#include <new>
#include <iterator>

template <typename T>
class DynamicArray {
public:
    explicit DynamicArray(std::pmr::memory_resource* memory_resource = std::pmr::get_default_resource());
    ~DynamicArray();

    void push_back(const T& value);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    size_t size() const;
    size_t capacity() const;

    class Iterator {
    public:
        Iterator(T* ptr) : ptr(ptr) {}

        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        bool operator==(const Iterator& other) const { return ptr == other.ptr; } 
    private:
        T* ptr;
    };

    Iterator begin();
    Iterator end();

private:
    std::pmr::memory_resource* memory_resource_;
    T* data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_capacity);
};


template <typename T>
DynamicArray<T>::DynamicArray(std::pmr::memory_resource* memory_resource)
    : memory_resource_(memory_resource), data_(nullptr), size_(0), capacity_(0) {}


template <typename T>
DynamicArray<T>::~DynamicArray() {
    for (size_t i = 0; i < size_; ++i) {
        std::destroy_at(&data_[i]);
    }
    memory_resource_->deallocate(data_, capacity_ * sizeof(T), alignof(T));
}

template <typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    std::construct_at(&data_[size_], value);
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
const T& DynamicArray<T>::operator[](size_t index) const {
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
    T* new_data = static_cast<T*>(memory_resource_->allocate(new_capacity * sizeof(T), alignof(T)));
    for (size_t i = 0; i < size_; ++i) {
        std::construct_at(&new_data[i], std::move(data_[i]));
        std::destroy_at(&data_[i]);
    }
    if (data_) {
        memory_resource_->deallocate(data_, capacity_ * sizeof(T), alignof(T));
    }
    data_ = new_data;
    capacity_ = new_capacity;
}

#endif // DYNAMIC_ARRAY_H
