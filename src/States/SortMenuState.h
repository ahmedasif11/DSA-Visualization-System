/**
 * @file SortMenuState.h
 * @brief Sorting algorithms menu state
 */

#pragma once

#include "../Core/State/State.h"
#include "../Core/State/StateID.h"
#include "../UI/Components/Button.h"
#include "../UI/Components/Label.h"
#include "../DSA/Algorithms/Sorting/SorterBase.h"
#include <vector>
#include <memory>
#include <functional>

namespace DSA {

/**
 * @class SortMenuState
 * @brief Menu state for selecting sorting algorithms
 * 
 * Displays a menu of available sorting algorithms:
 * - Bubble Sort
 * - Insertion Sort
 * - Selection Sort
 * - Back
 */
class SortMenuState : public State {
public:
    /**
     * @brief Callback function type for algorithm selection
     * @param sorter Unique pointer to selected sorter
     */
    using AlgorithmCallback = std::function<void(std::unique_ptr<SorterBase>)>;
    
    /**
     * @brief Construct a new SortMenuState
     * @param context State context
     */
    explicit SortMenuState(StateContext& context);
    
    /**
     * @brief Destructor
     */
    virtual ~SortMenuState() = default;
    
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
     * @brief Set callback for algorithm selection
     * @param callback Callback function
     */
    void setAlgorithmCallback(AlgorithmCallback callback);

private:
    /**
     * @brief Setup menu buttons
     */
    void setupButtons();
    
    /**
     * @brief Handle button clicks
     */
    void onBubbleSortClicked();
    void onInsertionSortClicked();
    void onSelectionSortClicked();
    void onBackClicked();

    UI::Label m_titleLabel;                              ///< Title label
    std::vector<std::unique_ptr<UI::Button>> m_buttons;  ///< Menu buttons
    sf::RectangleShape m_background;                     ///< Background
    AlgorithmCallback m_algorithmCallback;               ///< Callback for algorithm selection
    int m_selectedButtonIndex = 0;                       ///< Currently selected button
};

} // namespace DSA
