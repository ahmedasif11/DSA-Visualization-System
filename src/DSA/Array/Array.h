

#pragma once

#include <cstddef>
#include <cstdlib>
#include <stdexcept>

namespace DSA {


class Array {
public:
    
    Array();
    
    
    explicit Array(std::size_t size, int value = 0);
    
    
    Array(const Array& other);
    
    
    Array(Array&& other) noexcept;
    
    
    ~Array();
    
    
    Array& operator=(const Array& other);
    
    
    Array& operator=(Array&& other) noexcept;
    
    
    int& at(std::size_t index);
    
    
    const int& at(std::size_t index) const;
    
    
    int& operator[](std::size_t index) { return m_data[index]; }
    
    
    const int& operator[](std::size_t index) const { return m_data[index]; }
    
    
    std::size_t size() const noexcept { return m_size; }
    
    
    std::size_t capacity() const noexcept { return m_capacity; }
    
    
    bool isEmpty() const noexcept { return m_size == 0; }
    
    
    void pushBack(int value);
    
    
    void popBack();
    
    
    void insert(std::size_t index, int value);
    
    
    void remove(std::size_t index);
    
    
    void swap(std::size_t i, std::size_t j);
    
    
    void clear() noexcept { m_size = 0; }
    
    
    void generateRandom(std::size_t count, int min, int max);
    
    
    void resize(std::size_t newSize, int value = 0);
    
    
    void reserve(std::size_t newCapacity);

private:
    int* m_data;
    std::size_t m_size;
    std::size_t m_capacity;
    
    
    void allocate(std::size_t newCapacity);
    
    
    void deallocate();
    
    
    void ensureCapacity(std::size_t minCapacity);
};

} 
