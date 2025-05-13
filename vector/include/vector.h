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
    for (size_t i = 0; i < _size; ++i)
        newData[i] = data[i];
    delete[] data;
    data = newData;
    _capacity = newCap;
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

    size_t size() const {return size; }
    size_t capacity() const { return _capacity; }
    bool empty() const { return _size == 0; }




};















#endif // VECTOR_H