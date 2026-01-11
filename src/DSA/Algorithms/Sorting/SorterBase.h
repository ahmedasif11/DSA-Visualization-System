/**
 * @file SorterBase.h
 * @brief Base interface for all sorting algorithms
 */

#pragma once

#include "SortStep.h"
#include "../../Array/Array.h"
#include <string>
#include <vector>

namespace DSA {

/**
 * @class SorterBase
 * @brief Abstract base class for all sorting algorithms
 * 
 * All sorting algorithms must inherit from this class and implement
 * the sort method, which generates a sequence of SortSteps representing
 * the algorithm's execution.
 */
class SorterBase {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~SorterBase() = default;
    
    /**
     * @brief Sort an array and generate step-by-step execution
     * @param array Array to sort (will be copied, original not modified)
     * @return Vector of SortSteps representing the algorithm's execution
     */
    virtual std::vector<SortStep> sort(const Array& array) = 0;
    
    /**
     * @brief Get the name of the sorting algorithm
     * @return Name of the algorithm (e.g., "Bubble Sort")
     */
    virtual std::string getName() const = 0;
    
    /**
     * @brief Get a description of the sorting algorithm
     * @return Description string
     */
    virtual std::string getDescription() const = 0;
    
    /**
     * @brief Get time complexity of the algorithm
     * @return Time complexity string (e.g., "O(n²)")
     */
    virtual std::string getTimeComplexity() const = 0;
    
    /**
     * @brief Get space complexity of the algorithm
     * @return Space complexity string (e.g., "O(1)")
     */
    virtual std::string getSpaceComplexity() const = 0;

protected:
    /**
     * @brief Create a comparison step
     * @param array Current array state
     * @param indices Indices being compared
     * @param message Description of the comparison
     * @return SortStep representing the comparison
     */
    SortStep createCompareStep(const Array& array, 
                               const std::vector<std::size_t>& indices,
                               const std::string& message) const;
    
    /**
     * @brief Create a swap step
     * @param array Current array state (before swap)
     * @param i First index to swap
     * @param j Second index to swap
     * @param message Description of the swap
     * @return SortStep representing the swap (with array state after swap)
     */
    SortStep createSwapStep(const Array& array,
                           std::size_t i,
                           std::size_t j,
                           const std::string& message) const;
    
    /**
     * @brief Create a highlight step
     * @param array Current array state
     * @param indices Indices to highlight
     * @param message Description of the highlight
     * @return SortStep representing the highlight
     */
    SortStep createHighlightStep(const Array& array,
                                const std::vector<std::size_t>& indices,
                                const std::string& message) const;
    
    /**
     * @brief Create a completion step
     * @param array Final sorted array state
     * @return SortStep representing completion
     */
    SortStep createCompleteStep(const Array& array) const;
};

} // namespace DSA
