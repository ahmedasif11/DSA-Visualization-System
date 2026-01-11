#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <map>
#include "DSA/Array/Array.h"

namespace DSA {

enum class StepType : std::uint8_t {
    Compare = 0,
    Swap,
    Highlight,
    Complete
};

enum class ElementRole : std::uint8_t {
    None = 0,
    Key,
    Minimum,
    Maximum,
    Pivot,
    Sorted,
    Active,
    Compared,
    Swapped
};

struct SortStep {
    StepType type;
    std::vector<std::size_t> indices;
    std::map<std::size_t, ElementRole> roles;
    std::map<std::string, std::string> annotations;
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
    
    SortStep(StepType stepType, 
             const std::vector<std::size_t>& stepIndices,
             const std::map<std::size_t, ElementRole>& stepRoles,
             const std::string& stepMessage,
             const Array& state)
        : type(stepType)
        , indices(stepIndices)
        , roles(stepRoles)
        , message(stepMessage)
        , arrayState(state)
    {}
    
    void setRole(std::size_t index, ElementRole role) {
        roles[index] = role;
    }
    
    ElementRole getRole(std::size_t index) const {
        auto it = roles.find(index);
        return (it != roles.end()) ? it->second : ElementRole::None;
    }
    
    void setAnnotation(const std::string& key, const std::string& value) {
        annotations[key] = value;
    }
    
    std::string getAnnotation(const std::string& key) const {
        auto it = annotations.find(key);
        return (it != annotations.end()) ? it->second : "";
    }
    
    bool hasAnnotation(const std::string& key) const {
        return annotations.find(key) != annotations.end();
    }
};

}
