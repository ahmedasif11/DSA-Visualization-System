/**
 * @file VisualizerState.h
 * @brief Visualization screen state for algorithm execution
 */

#pragma once

#include "../Core/State/State.h"
#include "../Core/State/StateID.h"
#include "../DSA/Array/Array.h"
#include "../DSA/Algorithms/AlgorithmExecutor.h"
#include "../DSA/Algorithms/Sorting/SorterBase.h"
#include "../Visual/Visualizer/BarVisualizer.h"
#include "../UI/Components/Button.h"
#include "../UI/Components/Label.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

namespace DSA {

/**
 * @class VisualizerState
 * @brief State for visualizing sorting algorithm execution
 * 
 * Displays the array as bars and animates the sorting process
 * step-by-step. Provides controls for play/pause, speed, and navigation.
 */
class VisualizerState : public State {
public:
    /**
     * @brief Construct a new VisualizerState
     * @param context State context
     */
    explicit VisualizerState(StateContext& context);
    
    /**
     * @brief Destructor
     */
    virtual ~VisualizerState() = default;
    
    /**
     * @brief Handle input events
     * @param event The SFML event to process
     */
    void handleInput(const sf::Event& event) override;
    
    /**
     * @brief Update state logic
     * @param deltaTime Time elapsed since last frame (in seconds)
     */
    void update(float deltaTime) override;
    
    /**
     * @brief Render state to target
     * @param target The render target (window)
     */
    void render(sf::RenderTarget& target) override;
    
    /**
     * @brief Called when state is entered
     */
    void onEnter() override;
    
    /**
     * @brief Called when state is exited
     */
    void onExit() override;
    
    /**
     * @brief Set the array to visualize
     * @param array Array to visualize
     */
    void setArray(const Array& array);
    
    /**
     * @brief Set the sorter to use
     * @param sorter Unique pointer to sorter
     */
    void setSorter(std::unique_ptr<SorterBase> sorter);

private:
    Array m_array;                              ///< Array being sorted
    std::unique_ptr<SorterBase> m_sorter;      ///< Current sorting algorithm
    AlgorithmExecutor m_executor;               ///< Algorithm executor
    Visual::BarVisualizer m_visualizer;        ///< Bar chart renderer
    
    // UI Components
    UI::Label m_titleLabel;                    ///< Title label
    UI::Label m_statusLabel;                   ///< Status message label
    UI::Label m_stepLabel;                     ///< Step counter label
    UI::Button m_playPauseButton;              ///< Play/pause button
    UI::Button m_resetButton;                  ///< Reset button
    UI::Button m_backButton;                   ///< Back button
    
    sf::RectangleShape m_background;            ///< Background rectangle
    sf::RectangleShape m_infoPanel;            ///< Info panel background
    
    bool m_initialized;                        ///< Initialization flag
    
    /**
     * @brief Initialize UI components
     */
    void initializeUI();
    
    /**
     * @brief Update UI based on current state
     */
    void updateUI();
    
    /**
     * @brief Handle play/pause button click
     */
    void onPlayPauseClicked();
    
    /**
     * @brief Handle reset button click
     */
    void onResetClicked();
    
    /**
     * @brief Handle back button click
     */
    void onBackClicked();
    
    /**
     * @brief Generate default array if none set
     */
    void generateDefaultArray();
};

} // namespace DSA
