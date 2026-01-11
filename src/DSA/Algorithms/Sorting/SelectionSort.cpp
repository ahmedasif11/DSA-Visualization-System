/**
 * @file SelectionSort.cpp
 * @brief Implementation of Selection Sort algorithm
 */

#include "SelectionSort.h"
#include "../../Array/Array.h"
#include <sstream>

namespace DSA {

std::vector<SortStep> SelectionSort::sort(const Array& array) {
    std::vector<SortStep> steps;
    
    // Handle empty or single-element arrays
    if (array.size() <= 1) {
        if (array.size() == 1) {
            steps.push_back(createCompleteStep(array));
        }
        return steps;
    }
    
    // Create a working copy of the array
    Array workingArray = array;
    
    std::size_t n = workingArray.size();
    
    // Outer loop: one element at a time
    for (std::size_t i = 0; i < n - 1; ++i) {
        // Find the minimum element in the unsorted portion
        std::size_t minIndex = i;
        
        // Highlight current position
        std::ostringstream startMsg;
        startMsg << "Starting pass " << (i + 1) << ", searching for minimum from index " << i;
        std::vector<std::size_t> startIndices = {i};
        steps.push_back(createHighlightStep(workingArray, startIndices, startMsg.str()));
        
        // Search for minimum
        for (std::size_t j = i + 1; j < n; ++j) {
            // Compare current element with minimum found so far
            std::ostringstream compareMsg;
            compareMsg << "Comparing element at index " << j 
                       << " (value: " << workingArray[j] 
                       << ") with minimum at index " << minIndex 
                       << " (value: " << workingArray[minIndex] << ")";
            std::vector<std::size_t> compareIndices = {j, minIndex};
            steps.push_back(createCompareStep(workingArray, compareIndices, compareMsg.str()));
            
            // Update minimum if current element is smaller
            if (workingArray[j] < workingArray[minIndex]) {
                minIndex = j;
                
                std::ostringstream newMinMsg;
                newMinMsg << "New minimum found at index " << minIndex 
                          << " (value: " << workingArray[minIndex] << ")";
                std::vector<std::size_t> minIndices = {minIndex};
                steps.push_back(createHighlightStep(workingArray, minIndices, newMinMsg.str()));
            }
        }
        
        // Swap minimum with first element of unsorted portion
        if (minIndex != i) {
            std::ostringstream swapMsg;
            swapMsg << "Swapping minimum at index " << minIndex 
                    << " (value: " << workingArray[minIndex] 
                    << ") with element at index " << i 
                    << " (value: " << workingArray[i] << ")";
            steps.push_back(createSwapStep(workingArray, i, minIndex, swapMsg.str()));
            
            // Perform the swap on working array
            workingArray.swap(i, minIndex);
        } else {
            // Element already in correct position
            std::ostringstream noSwapMsg;
            noSwapMsg << "Element at index " << i 
                      << " is already in correct position";
            std::vector<std::size_t> noSwapIndices = {i};
            steps.push_back(createHighlightStep(workingArray, noSwapIndices, noSwapMsg.str()));
        }
        
        // Highlight sorted portion
        std::ostringstream sortedMsg;
        sortedMsg << "Elements up to index " << i << " are now sorted";
        std::vector<std::size_t> sortedIndices;
        for (std::size_t k = 0; k <= i; ++k) {
            sortedIndices.push_back(k);
        }
        steps.push_back(createHighlightStep(workingArray, sortedIndices, sortedMsg.str()));
    }
    
    // Add completion step
    steps.push_back(createCompleteStep(workingArray));
    
    return steps;
}

std::string SelectionSort::getDescription() const {
    return "Selection Sort repeatedly finds the minimum element from the "
           "unsorted portion and places it at the beginning. "
           "Similar to repeatedly selecting the smallest card from a deck.";
}

} // namespace DSA
