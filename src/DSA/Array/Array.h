/**
 * @file Array.h
 * @brief Custom Array container implementation (no STL)
 */

#pragma once

#include <cstddef>
#include <cstdlib>
#include <stdexcept>

namespace DSA {

/**
 * @class Array
 * @brief Custom dynamic array container (STL-free implementation)
 * 
 * This class provides a custom array implementation without using STL containers.
 * Used for core DSA logic as per project requirements.
 */
class Array {
public:
    /**
     * @brief Default constructor
     * Creates an empty array
     */
    Array();
    
    /**
     * @brief Constructor with initial size
     * @param size Initial size of the array
     * @param value Initial value for all elements (default: 0)
     */
    explicit Array(std::size_t size, int value = 0);
    
    /**
     * @brief Copy constructor
     * @param other Array to copy from
     */
    Array(const Array& other);
    
    /**
     * @brief Move constructor
     * @param other Array to move from
     */
    Array(Array&& other) noexcept;
    
    /**
     * @brief Destructor
     */
    ~Array();
    
    /**
     * @brief Copy assignment operator
     * @param other Array to copy from
     * @return Reference to this array
     */
    Array& operator=(const Array& other);
    
    /**
     * @brief Move assignment operator
     * @param other Array to move from
     * @return Reference to this array
     */
    Array& operator=(Array&& other) noexcept;
    
    /**
     * @brief Access element at index (bounds checked)
     * @param index Index of the element
     * @return Reference to the element
     * @throws std::out_of_range if index is invalid
     */
    int& at(std::size_t index);
    
    /**
     * @brief Access element at index (const version)
     * @param index Index of the element
     * @return Const reference to the element
     * @throws std::out_of_range if index is invalid
     */
    const int& at(std::size_t index) const;
    
    /**
     * @brief Access element at index (no bounds check)
     * @param index Index of the element
     * @return Reference to the element
     */
    int& operator[](std::size_t index) { return m_data[index]; }
    
    /**
     * @brief Access element at index (const version, no bounds check)
     * @param index Index of the element
     * @return Const reference to the element
     */
    const int& operator[](std::size_t index) const { return m_data[index]; }
    
    /**
     * @brief Get the current size of the array
     * @return Size of the array
     */
    std::size_t size() const noexcept { return m_size; }
    
    /**
     * @brief Get the capacity of the array
     * @return Capacity of the array
     */
    std::size_t capacity() const noexcept { return m_capacity; }
    
    /**
     * @brief Check if the array is empty
     * @return true if array is empty
     */
    bool isEmpty() const noexcept { return m_size == 0; }
    
    /**
     * @brief Add an element to the end of the array
     * @param value Value to add
     */
    void pushBack(int value);
    
    /**
     * @brief Remove the last element
     */
    void popBack();
    
    /**
     * @brief Insert an element at a specific index
     * @param index Index to insert at
     * @param value Value to insert
     * @throws std::out_of_range if index is invalid
     */
    void insert(std::size_t index, int value);
    
    /**
     * @brief Remove an element at a specific index
     * @param index Index to remove
     * @throws std::out_of_range if index is invalid
     */
    void remove(std::size_t index);
    
    /**
     * @brief Swap two elements
     * @param i First index
     * @param j Second index
     * @throws std::out_of_range if either index is invalid
     */
    void swap(std::size_t i, std::size_t j);
    
    /**
     * @brief Clear all elements (does not deallocate memory)
     */
    void clear() noexcept { m_size = 0; }
    
    /**
     * @brief Fill the array with random values
     * @param count Number of elements to generate
     * @param min Minimum value (inclusive)
     * @param max Maximum value (inclusive)
     */
    void generateRandom(std::size_t count, int min, int max);
    
    /**
     * @brief Resize the array
     * @param newSize New size
     * @param value Value to use for new elements (default: 0)
     */
    void resize(std::size_t newSize, int value = 0);
    
    /**
     * @brief Reserve capacity for the array
     * @param newCapacity New capacity
     */
    void reserve(std::size_t newCapacity);

private:
    int* m_data;           ///< Pointer to the data
    std::size_t m_size;    ///< Current number of elements
    std::size_t m_capacity; ///< Allocated capacity
    
    /**
     * @brief Allocate memory for the array
     * @param newCapacity Capacity to allocate
     */
    void allocate(std::size_t newCapacity);
    
    /**
     * @brief Deallocate memory
     */
    void deallocate();
    
    /**
     * @brief Ensure capacity is sufficient for size
     * @param minCapacity Minimum capacity needed
     */
    void ensureCapacity(std::size_t minCapacity);
};

} // namespace DSA
