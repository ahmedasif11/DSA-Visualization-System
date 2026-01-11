/**
 * @file AlgorithmMenuState.h
 * @brief Algorithm category menu state
 */

#pragma once

#include "../Core/State/State.h"
#include "../Core/State/StateID.h"
#include "../UI/Components/Button.h"
#include "../UI/Components/Label.h"
#include <vector>
#include <memory>

namespace DSA {

/**
 * @class AlgorithmMenuState
 * @brief Menu state for selecting algorithm categories
 * 
 * Displays a menu of algorithm categories:
 * - Sorting Algorithms
 * - Data Structures (locked)
 * - Back
 */
class AlgorithmMenuState : public State {
public:
    /**
     * @brief Construct a new AlgorithmMenuState
     * @param context State context
     */
    explicit AlgorithmMenuState(StateContext& context);
    
    /**
     * @brief Destructor
     */
    virtual ~AlgorithmMenuState() = default;
    
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

private:
    /**
     * @brief Setup menu buttons
     */
    void setupButtons();
    
    /**
     * @brief Handle button clicks
     */
    void onSortingAlgorithmsClicked();
    void onBackClicked();

    UI::Label m_titleLabel;                              ///< Title label
    std::vector<std::unique_ptr<UI::Button>> m_buttons;  ///< Menu buttons
    sf::RectangleShape m_background;                     ///< Background
    int m_selectedButtonIndex = 0;                       ///< Currently selected button
};

} // namespace DSA
