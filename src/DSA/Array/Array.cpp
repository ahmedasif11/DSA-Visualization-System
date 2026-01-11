

#include "Array.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <random>

namespace DSA {

static constexpr std::size_t INITIAL_CAPACITY = 8;
static constexpr std::size_t GROWTH_FACTOR = 2;

Array::Array()
    : m_data(nullptr)
    , m_size(0)
    , m_capacity(0)
{
}

Array::Array(std::size_t size, int value)
    : m_data(nullptr)
    , m_size(size)
    , m_capacity(size > 0 ? size : INITIAL_CAPACITY)
{
    if (m_capacity > 0) {
        allocate(m_capacity);

        for (std::size_t i = 0; i < m_size; ++i) {
            m_data[i] = value;
        }
    }
}

Array::Array(const Array& other)
    : m_data(nullptr)
    , m_size(other.m_size)
    , m_capacity(other.m_capacity)
{
    if (m_capacity > 0 && m_size > 0) {
        allocate(m_capacity);

        for (std::size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }
}

Array::Array(Array&& other) noexcept
    : m_data(other.m_data)
    , m_size(other.m_size)
    , m_capacity(other.m_capacity)
{
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

Array::~Array() {
    deallocate();
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        m_size = other.m_size;

        if (m_capacity < other.m_size) {
            deallocate();
            m_capacity = other.m_size > 0 ? other.m_size : 0;
            if (m_capacity > 0) {
                allocate(m_capacity);
            }
        }

        if (m_size > 0 && m_data) {
            for (std::size_t i = 0; i < m_size; ++i) {
                m_data[i] = other.m_data[i];
            }
        }
    }
    return *this;
}

Array& Array::operator=(Array&& other) noexcept {
    if (this != &other) {
        deallocate();
        
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    return *this;
}

int& Array::at(std::size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("Array index out of range");
    }
    return m_data[index];
}

const int& Array::at(std::size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("Array index out of range");
    }
    return m_data[index];
}

void Array::pushBack(int value) {
    ensureCapacity(m_size + 1);
    m_data[m_size] = value;
    ++m_size;
}

void Array::popBack() {
    if (m_size > 0) {
        --m_size;
    }
}

void Array::insert(std::size_t index, int value) {
    if (index > m_size) {
        throw std::out_of_range("Array index out of range for insert");
    }
    
    ensureCapacity(m_size + 1);

    for (std::size_t i = m_size; i > index; --i) {
        m_data[i] = m_data[i - 1];
    }
    
    m_data[index] = value;
    ++m_size;
}

void Array::remove(std::size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("Array index out of range for remove");
    }

    for (std::size_t i = index; i < m_size - 1; ++i) {
        m_data[i] = m_data[i + 1];
    }
    
    --m_size;
}

void Array::swap(std::size_t i, std::size_t j) {
    if (i >= m_size || j >= m_size) {
        throw std::out_of_range("Array index out of range for swap");
    }
    
    int temp = m_data[i];
    m_data[i] = m_data[j];
    m_data[j] = temp;
}

void Array::generateRandom(std::size_t count, int min, int max) {
    if (count == 0) {
        clear();
        return;
    }
    
    ensureCapacity(count);
    m_size = count;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    
    for (std::size_t i = 0; i < count; ++i) {
        m_data[i] = dis(gen);
    }
}

void Array::resize(std::size_t newSize, int value) {
    if (newSize > m_capacity) {
        ensureCapacity(newSize);
    }

    for (std::size_t i = m_size; i < newSize; ++i) {
        m_data[i] = value;
    }
    
    m_size = newSize;
}

void Array::reserve(std::size_t newCapacity) {
    if (newCapacity > m_capacity) {
        ensureCapacity(newCapacity);
    }
}

void Array::allocate(std::size_t newCapacity) {
    if (newCapacity == 0) {
        m_data = nullptr;
        return;
    }

    m_data = static_cast<int*>(std::malloc(newCapacity * sizeof(int)));
    if (!m_data) {
        throw std::bad_alloc();
    }
}

void Array::deallocate() {
    if (m_data) {
        std::free(m_data);
        m_data = nullptr;
    }
    m_capacity = 0;
}

void Array::ensureCapacity(std::size_t minCapacity) {
    if (minCapacity <= m_capacity) {
        return;
    }

    std::size_t newCapacity = m_capacity == 0 ? INITIAL_CAPACITY : m_capacity;
    while (newCapacity < minCapacity) {
        newCapacity *= GROWTH_FACTOR;
    }

    int* newData = static_cast<int*>(std::malloc(newCapacity * sizeof(int)));
    if (!newData) {
        throw std::bad_alloc();
    }

    if (m_data) {
        for (std::size_t i = 0; i < m_size; ++i) {
            newData[i] = m_data[i];
        }
        std::free(m_data);
    }
    
    m_data = newData;
    m_capacity = newCapacity;
}

} 
