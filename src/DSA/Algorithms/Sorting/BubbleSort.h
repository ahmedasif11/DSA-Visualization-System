/**
 * @file BubbleSort.h
 * @brief Bubble Sort algorithm implementation
 */

#pragma once

#include "SorterBase.h"

namespace DSA {

/**
 * @class BubbleSort
 * @brief Implementation of the Bubble Sort algorithm
 * 
 * Bubble Sort repeatedly steps through the list, compares adjacent elements
 * and swaps them if they are in the wrong order. The pass through the list
 * is repeated until the list is sorted.
 * 
 * Time Complexity: O(n²)
 * Space Complexity: O(1)
 */
class BubbleSort : public SorterBase {
public:
    /**
     * @brief Default constructor
     */
    BubbleSort() = default;
    
    /**
     * @brief Destructor
     */
    virtual ~BubbleSort() = default;
    
    /**
     * @brief Sort an array using Bubble Sort
     * @param array Array to sort
     * @return Vector of SortSteps representing the algorithm's execution
     */
    std::vector<SortStep> sort(const Array& array) override;
    
    /**
     * @brief Get the name of the algorithm
     * @return "Bubble Sort"
     */
    std::string getName() const override { return "Bubble Sort"; }
    
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
