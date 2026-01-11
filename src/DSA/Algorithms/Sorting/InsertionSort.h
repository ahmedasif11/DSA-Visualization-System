/**
 * @file InsertionSort.h
 * @brief Insertion Sort algorithm implementation
 */

#pragma once

#include "SorterBase.h"

namespace DSA {

/**
 * @class InsertionSort
 * @brief Implementation of the Insertion Sort algorithm
 * 
 * Insertion Sort builds a sorted array one element at a time by
 * inserting each element into its correct position in the sorted portion.
 * 
 * Time Complexity: O(n²)
 * Space Complexity: O(1)
 */
class InsertionSort : public SorterBase {
public:
    /**
     * @brief Default constructor
     */
    InsertionSort() = default;
    
    /**
     * @brief Destructor
     */
    virtual ~InsertionSort() = default;
    
    /**
     * @brief Sort an array using Insertion Sort
     * @param array Array to sort
     * @return Vector of SortSteps representing the algorithm's execution
     */
    std::vector<SortStep> sort(const Array& array) override;
    
    /**
     * @brief Get the name of the algorithm
     * @return "Insertion Sort"
     */
    std::string getName() const override { return "Insertion Sort"; }
    
    /**
     * @brief Get the description of the algorithm
     * @return Description string
     */
    std::string getDescription() const override;
    
    /**
     * @brief Get time complexity
     * @return "O(n²)"
     */
    std::string getTimeComplexity() const override { return "O(n²)"; }
    
    /**
     * @brief Get space complexity
     * @return "O(1)"
     */
    std::string getSpaceComplexity() const override { return "O(1)"; }
};

} // namespace DSA
