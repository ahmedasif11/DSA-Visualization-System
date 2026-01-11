#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include "DSA/Array/Array.h"

namespace DSA {

enum class StepType : std::uint8_t {
    Compare = 0,
    Swap,
    Highlight,
    Complete
};

struct SortStep {
    StepType type;
    std::vector<std::size_t> indices;
    std::string message;
    Array arrayState;
    
    SortStep() = default;
    
    SortStep(StepType stepType, 
             const std::vector<std::size_t>& stepIndices,
             const std::string& stepMessage,
             const Array& state)
        : type(stepType)
        , indices(stepIndices)
        , message(stepMessage)
        , arrayState(state)
    {}
};

}
