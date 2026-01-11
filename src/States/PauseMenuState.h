/**
 * @file PauseMenuState.h
 * @brief Pause menu overlay state
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
 * @class PauseMenuState
 * @brief Pause menu overlay state
 * 
 * Displays pause menu overlay with options:
 * - Resume
 * - Main Menu
 * - Exit
 */
class PauseMenuState : public State {
public:
    /**
     * @brief Construct a new PauseMenuState
     * @param context State context
     */
    explicit PauseMenuState(StateContext& context);
    
    /**
     * @brief Destructor
     */
    virtual ~PauseMenuState() = default;
    
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
    void onResumeClicked();
    void onMainMenuClicked();
    void onExitClicked();

    UI::Label m_titleLabel;                              ///< Title label
    std::vector<std::unique_ptr<UI::Button>> m_buttons;  ///< Menu buttons
    sf::RectangleShape m_overlay;                        ///< Semi-transparent overlay
    sf::RectangleShape m_menuBackground;                 ///< Menu background
    int m_selectedButtonIndex = 0;                       ///< Currently selected button
};

} // namespace DSA
