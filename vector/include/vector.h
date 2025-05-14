#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <cmath>


template<typename T>
class Vector{

private:

    T* data;
    size_t size_;
    size_t capacity_;

    //helper
    void reallocate(size_t newCap) {
    T* newData = new T[newCap];
    for (size_t i = 0; i < size_; ++i)
        newData[i] = data[i];
    delete[] data;
    data = newData;
    capacity_ = newCap;
    }

public:

    //constructor

    Vector() : data(nullptr), size_(0), capacity_(0) {}

    Vector(std::initializer_list<T> init) : data(nullptr), size_(0), capacity_(0) {}
    
    //destructor

    ~Vector(){
        delete[] data;
    }

    //copy ctor

    Vector(const Vector other): data(nullptr), size_(other.size_), capacity_(other.capacity_) {

        if (_capacity) {
            data = new T[_capacity];
            for (size_t i = 0; i < _size; ++i)
                data[i] = other.data[i];
        }
    }

    //copy assg

    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;
        delete[] data;
        _size = other._size;
        _capacity = other._capacity;
        data = nullptr;
        if (_capacity) {

            data = new T[_capacity];
            for (size_t i = 0; i < _size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    //move ctor

    Vector(Vector&& other) noexcept : data(other.data), size_(other.size_), capacity_(other.capacity_) {
        other.data = nullptr;
        other.size_ = other.capacity_ = 0;
    }

    //move assg

    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;
        data = other.data;
        _size = other._size;
        _capacity = other._capacity;
        other.data = nullptr;
        other._size = other._capacity = 0;
        return *this;
    }

    //overloads

    bool operator==(const Vector& other) const {
        if (size_ != other.size_) 
            return false;
        for (size_t i = 0; i < size_; ++i) {
            if (data[i] != other.data[i]) 
                return false;
        }
        return true;
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    size_t size() const {return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    //push_back
    void push_back(const T& value) {
        if (size_ == capacity_) {
            size_t newCap = capacity_ == 0 ? 1 : capacity_ * 2;
            reallocate(newCap);
        }
        data[size_] = value;
        ++size_;
    }

    //pop_back
    void pop_back() {
        if (size_ == 0)
            throw std::out_of_range("pop_back() on empty Vector");
        --size_;
    }


    using iterator = T*;
    using const_iterator = const T*;

    T* data_ptr() { return data; }
    const T* data_ptr() const { return data; }

    
    iterator begin() { return data; }
    const_iterator begin() const { return data; }
    iterator end() { return data + size_; }
    const_iterator end() const { return data + size_; }

    void swap(Vector& other) noexcept {
        std::swap(data,      other.data);
        std::swap(size_,     other.size_);
        std::swap(capacity_, other.capacity_);
    }

    void assign(size_t n, const T& value) {
        if (n > capacity_) reserve(n);
        for (size_t i = 0; i < n; ++i)
            data[i] = value;
        size_ = n;
    }

    template<typename InputIt>
    void assign(InputIt first, InputIt last) {
        size_t n = std::distance(first, last);
        if (n > capacity_) reserve(n);
        size_t i = 0;
        for (auto it = first; it != last; ++it, ++i)
            data[i] = *it;
        size_ = n;
    }

    iterator insert(const_iterator pos, const T& value) {
        size_t idx = pos - data;               // index to insert at
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        for (size_t i = size_; i > idx; --i)
            data[i] = data[i-1];
        data[idx] = value;
        ++size_;
        return data + idx;
    }

    iterator erase(const_iterator pos) {
        size_t idx = pos - data;
        if (idx >= size_) return end();
        for (size_t i = idx; i + 1 < size_; ++i)
            data[i] = data[i+1];
        --size_;
        return data + idx;
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data[size_] = T(std::forward<Args>(args)...);
        ++size_;
    }


};















#endif // VECTOR_H