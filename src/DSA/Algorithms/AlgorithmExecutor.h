

#pragma once

#include "Sorting/SorterBase.h"
#include "Sorting/SortStep.h"
#include "../Array/Array.h"
#include <vector>
#include <memory>
#include <cstddef>

namespace DSA {


class AlgorithmExecutor {
public:
    
    enum class State {
        Idle,
        Running,
        Paused,
        Completed
    };
    
    
    AlgorithmExecutor();
    
    
    ~AlgorithmExecutor() = default;
    
    
    void setSorter(std::unique_ptr<SorterBase> sorter);
    
    
    void setArray(const Array& array);
    
    
    bool start();
    
    
    void pause();
    
    
    void resume();
    
    
    void reset();
    
    
    void stepForward();
    
    
    void setSpeed(float speed);
    
    
    void update(float deltaTime);
    
    
    const SortStep* getCurrentStep() const;
    
    
    std::size_t getCurrentStepIndex() const { return m_currentStepIndex; }
    
    
    std::size_t getTotalSteps() const { return m_steps.size(); }
    
    
    bool isCompleted() const { return m_state == State::Completed; }
    
    
    State getState() const { return m_state; }
    
    
    std::string getCurrentMessage() const;
    
    
    std::string getAlgorithmName() const;

private:
    std::unique_ptr<SorterBase> m_sorter;
    Array m_array;
    std::vector<SortStep> m_steps;
    std::size_t m_currentStepIndex;
    State m_state;
    
    float m_speed;
    float m_timeSinceLastStep;
    float m_stepDelay;
    
    
    void advanceStep();
    
    
    float calculateStepDelay(const SortStep& step) const;
};

} 
