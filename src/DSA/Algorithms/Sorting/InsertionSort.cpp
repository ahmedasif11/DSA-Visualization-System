/**
 * @file InsertionSort.cpp
 * @brief Implementation of Insertion Sort algorithm
 */

#include "InsertionSort.h"
#include "../../Array/Array.h"
#include <sstream>

namespace DSA {

std::vector<SortStep> InsertionSort::sort(const Array& array) {
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
    
    // Start from the second element (index 1)
    for (std::size_t i = 1; i < n; ++i) {
        int key = workingArray[i];
        std::size_t j = i;
        
        // Highlight the current element being inserted
        std::ostringstream highlightMsg;
        highlightMsg << "Selecting element at index " << i 
                     << " (value: " << key << ") to insert";
        std::vector<std::size_t> highlightIndices = {i};
        steps.push_back(createHighlightStep(workingArray, highlightIndices, highlightMsg.str()));
        
        // Move elements greater than key one position ahead
        while (j > 0 && workingArray[j - 1] > key) {
            // Compare with previous element
            std::ostringstream compareMsg;
            compareMsg << "Comparing element at index " << (j - 1) 
                       << " (value: " << workingArray[j - 1] 
                       << ") with key (value: " << key << ")";
            std::vector<std::size_t> compareIndices = {j - 1, j};
            steps.push_back(createCompareStep(workingArray, compareIndices, compareMsg.str()));
            
            // Shift element to the right
            workingArray[j] = workingArray[j - 1];
            --j;
            
            // Show the shift (visual representation)
            std::ostringstream shiftMsg;
            shiftMsg << "Shifting element at index " << (j) 
                     << " to index " << (j + 1);
            std::vector<std::size_t> shiftIndices = {j, j + 1};
            steps.push_back(createHighlightStep(workingArray, shiftIndices, shiftMsg.str()));
        }
        
        // Insert key at correct position
        if (j != i) {
            workingArray[j] = key;
            
            std::ostringstream insertMsg;
            insertMsg << "Inserting key at index " << j;
            std::vector<std::size_t> insertIndices = {j};
            steps.push_back(createHighlightStep(workingArray, insertIndices, insertMsg.str()));
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

std::string InsertionSort::getDescription() const {
    return "Insertion Sort builds a sorted array one element at a time by "
           "inserting each element into its correct position in the sorted portion. "
           "Similar to how you sort playing cards in your hand.";
}

} // namespace DSA
