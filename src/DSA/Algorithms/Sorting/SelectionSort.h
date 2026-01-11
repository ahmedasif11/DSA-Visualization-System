/**
 * @file SelectionSort.h
 * @brief Selection Sort algorithm implementation
 */

#pragma once

#include "SorterBase.h"

namespace DSA {

/**
 * @class SelectionSort
 * @brief Implementation of the Selection Sort algorithm
 * 
 * Selection Sort repeatedly finds the minimum element from the unsorted
 * portion and places it at the beginning.
 * 
 * Time Complexity: O(n²)
 * Space Complexity: O(1)
 */
class SelectionSort : public SorterBase {
public:
    /**
     * @brief Default constructor
     */
    SelectionSort() = default;
    
    /**
     * @brief Destructor
     */
    virtual ~SelectionSort() = default;
    
    /**
     * @brief Sort an array using Selection Sort
     * @param array Array to sort
     * @return Vector of SortSteps representing the algorithm's execution
     */
    std::vector<SortStep> sort(const Array& array) override;
    
    /**
     * @brief Get the name of the algorithm
     * @return "Selection Sort"
     */
    std::string getName() const override { return "Selection Sort"; }
    
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
