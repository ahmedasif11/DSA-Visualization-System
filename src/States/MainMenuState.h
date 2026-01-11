/**
 * @file MainMenuState.h
 * @brief Main menu state
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
 * @class MainMenuState
 * @brief Main menu state
 * 
 * Displays main menu with options:
 * - Algorithms
 * - Data Structures (locked)
 * - Exit
 */
class MainMenuState : public State {
public:
    /**
     * @brief Construct a new MainMenuState
     * @param context State context
     */
    explicit MainMenuState(StateContext& context);
    
    /**
     * @brief Destructor
     */
    virtual ~MainMenuState() = default;
    
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
    void onAlgorithmsClicked();
    void onExitClicked();

    UI::Label m_titleLabel;                    ///< Title label
    std::vector<std::unique_ptr<UI::Button>> m_buttons;  ///< Menu buttons
    sf::RectangleShape m_background;           ///< Background
    int m_selectedButtonIndex = 0;            ///< Currently selected button (for keyboard navigation)
};

} // namespace DSA
