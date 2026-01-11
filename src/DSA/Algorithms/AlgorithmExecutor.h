/**
 * @file AlgorithmExecutor.h
 * @brief Algorithm execution engine for step-by-step visualization
 */

#pragma once

#include "Sorting/SorterBase.h"
#include "Sorting/SortStep.h"
#include "../Array/Array.h"
#include <vector>
#include <memory>
#include <cstddef>

namespace DSA {

/**
 * @class AlgorithmExecutor
 * @brief Executes sorting algorithms step-by-step with timing control
 * 
 * Manages the execution of sorting algorithms, controlling the speed
 * of step progression and providing access to current step state.
 */
class AlgorithmExecutor {
public:
    /**
     * @brief Execution state
     */
    enum class State {
        Idle,       ///< No algorithm running
        Running,    ///< Algorithm executing
        Paused,     ///< Algorithm paused
        Completed   ///< Algorithm finished
    };
    
    /**
     * @brief Default constructor
     */
    AlgorithmExecutor();
    
    /**
     * @brief Destructor
     */
    ~AlgorithmExecutor() = default;
    
    /**
     * @brief Set the sorter to use
     * @param sorter Unique pointer to sorter (takes ownership)
     */
    void setSorter(std::unique_ptr<SorterBase> sorter);
    
    /**
     * @brief Set the array to sort
     * @param array Array to sort
     */
    void setArray(const Array& array);
    
    /**
     * @brief Start algorithm execution
     * @return true if started successfully, false otherwise
     */
    bool start();
    
    /**
     * @brief Pause algorithm execution
     */
    void pause();
    
    /**
     * @brief Resume algorithm execution
     */
    void resume();
    
    /**
     * @brief Reset to initial state
     */
    void reset();
    
    /**
     * @brief Step forward one step (manual control)
     */
    void stepForward();
    
    /**
     * @brief Set animation speed multiplier
     * @param speed Speed multiplier (1.0 = normal, 2.0 = double speed, etc.)
     */
    void setSpeed(float speed);
    
    /**
     * @brief Update executor (call each frame)
     * @param deltaTime Time elapsed since last frame (in seconds)
     */
    void update(float deltaTime);
    
    /**
     * @brief Get current step
     * @return Pointer to current step, or nullptr if none
     */
    const SortStep* getCurrentStep() const;
    
    /**
     * @brief Get current step index
     * @return Current step index
     */
    std::size_t getCurrentStepIndex() const { return m_currentStepIndex; }
    
    /**
     * @brief Get total number of steps
     * @return Total steps
     */
    std::size_t getTotalSteps() const { return m_steps.size(); }
    
    /**
     * @brief Check if algorithm is completed
     * @return true if completed
     */
    bool isCompleted() const { return m_state == State::Completed; }
    
    /**
     * @brief Get current execution state
     * @return Current state
     */
    State getState() const { return m_state; }
    
    /**
     * @brief Get current step message
     * @return Message string, or empty if no step
     */
    std::string getCurrentMessage() const;
    
    /**
     * @brief Get algorithm name
     * @return Algorithm name, or empty if no sorter set
     */
    std::string getAlgorithmName() const;

private:
    std::unique_ptr<SorterBase> m_sorter;  ///< Current sorter
    Array m_array;                         ///< Array being sorted
    std::vector<SortStep> m_steps;         ///< All steps generated
    std::size_t m_currentStepIndex;        ///< Current step index
    State m_state;                         ///< Current execution state
    
    float m_speed;                         ///< Speed multiplier
    float m_timeSinceLastStep;             ///< Time accumulator
    float m_stepDelay;                     ///< Delay between steps (in seconds)
    
    /**
     * @brief Advance to next step
     */
    void advanceStep();
    
    /**
     * @brief Calculate step delay based on step type
     * @param step Step to calculate delay for
     * @return Delay in seconds
     */
    float calculateStepDelay(const SortStep& step) const;
};

} // namespace DSA
