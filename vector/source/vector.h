#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <utility>

template<typename T>
class Vector {
private:
    T* data;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t newCap) {
        T* newData = new T[newCap];
        for (size_t i = 0; i < size_; ++i)
            newData[i] = std::move(data[i]);
        delete[] data;
        data     = newData;
        capacity_ = newCap;
    }

public:
    // default ctor
    Vector() : data(nullptr), size_(0), capacity_(0) {}

    // initializer-list ctor
    Vector(std::initializer_list<T> init)
      : data(nullptr), size_(0), capacity_(0)
    {
        reserve(init.size());
        for (const auto& x : init)
            push_back(x);
    }

    // destructor
    ~Vector() {
        delete[] data;
    }

    // copy ctor
    Vector(const Vector& other)
      : data(nullptr), size_(other.size_), capacity_(other.capacity_)
    {
        if (capacity_) {
            data = new T[capacity_];
            for (size_t i = 0; i < size_; ++i)
                data[i] = other.data[i];
        }
    }

    // copy assignment
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data = nullptr;
            if (capacity_) {
                data = new T[capacity_];
                for (size_t i = 0; i < size_; ++i)
                    data[i] = other.data[i];
            }
        }
        return *this;
    }

    // move ctor
    Vector(Vector&& other) noexcept
      : data(other.data), size_(other.size_), capacity_(other.capacity_)
    {
        other.data = nullptr;
        other.size_ = 0;
        other.capacity_= 0;
    }

    // move assignment
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // element comparisons
    bool operator==(const Vector& o) const {
        if (size_ != o.size_) return false;
        for (size_t i = 0; i < size_; ++i)
            if (data[i] != o.data[i]) return false;
        return true;
    }
    bool operator!=(const Vector& o) const {
        return !(*this == o);
    }

    // capacity
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool   empty() const { return size_ == 0; }

    void reserve(size_t newCap) {
        if (newCap > capacity_) reallocate(newCap);
    }

    void shrink_to_fit() {
        if (capacity_ > size_) reallocate(size_);
    }

    void clear() noexcept {
        size_ = 0;
    }

    void resize(size_t count, const T& value = T()) {
        if (count > capacity_) reserve(count);
        for (size_t i = size_; i < count; ++i)
            data[i] = value;
        size_ = count;
    }

    // modifiers
    void push_back(const T& value) {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data[size_++] = value;
    }

    void pop_back() {
        if (size_ == 0)
            throw std::out_of_range("pop_back() on empty Vector");
        data[--size_].~T();
    }

    void swap(Vector& other) noexcept {
        std::swap(data, other.data);
        std::swap(size_, other.size_);
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
        clear();
        for (; first != last; ++first)
            push_back(*first);
    }

    // insert / erase
    using iterator = T*;
    using const_iterator = const T*;

    iterator begin() { return data; }
    const_iterator begin() const { return data; }
    iterator end() { return data + size_; }
    const_iterator end() const { return data + size_; }

    iterator insert(const_iterator pos, const T& value) {
        size_t idx = pos - data;
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        for (size_t i = size_; i > idx; --i)
            data[i] = data[i-1];
        data[idx] = value;
        ++size_;
        return data + idx;
    }

    iterator erase(const_iterator pos){
        size_t idx = pos - data;
        if (idx >= size_){
            return end();
        }
        for (size_t i = idx; i + 1 < size_; ++i) {
            data[i] = std::move(data[i+1]);
        }
        --size_;
        return data + idx;
    }


    // emplacement
    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ == capacity_)
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data[size_] = T(std::forward<Args>(args)...);
        ++size_;
    }

    // element access
    T&       operator[](size_t i)       { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }

    T&       at(size_t i) {
        if (i >= size_) throw std::out_of_range("Vector::at");
        return data[i];
    }
    const T& at(size_t i) const {
        if (i >= size_) throw std::out_of_range("Vector::at");
        return data[i];
    }

    T& front() { return at(0); }
    const T& front() const { return at(0); }
    T& back() { return at(size_-1); }
    const T& back()  const { return at(size_-1); }

    // assign from initializer_list
    Vector& operator=(std::initializer_list<T> init) {
        assign(init.begin(), init.end());
        return *this;
    }

    // grant friend access for operator<
    template<typename U>
    friend bool operator< (const Vector<U>& a, const Vector<U>& b);
};

// free swap for ADL
template<typename T>
void swap(Vector<T>& a, Vector<T>& b) noexcept {
    a.swap(b);
}

// relational operators
template<typename T>
bool operator< (const Vector<T>& a, const Vector<T>& b) {
    return std::lexicographical_compare(
        a.begin(), a.end(),
        b.begin(), b.end()
    );
}

template<typename T>
bool operator> (const Vector<T>& a, const Vector<T>& b) { return b < a; }

template<typename T>
bool operator<= (const Vector<T>& a, const Vector<T>& b) { return !(b < a); }

template<typename T>
bool operator>= (const Vector<T>& a, const Vector<T>& b) { return !(a < b); }

#endif // VECTOR_H
