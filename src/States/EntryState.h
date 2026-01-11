/**
 * @file EntryState.h
 * @brief Entry/splash screen state
 */

#pragma once

#include "../Core/State/State.h"
#include "../Core/State/StateID.h"
#include "../UI/Components/Label.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>

namespace DSA {

/**
 * @class EntryState
 * @brief Entry/splash screen state
 * 
 * Displays logo/title, loading indicator, and "Press any key" message.
 * Transitions to MainMenu on any input or after timeout.
 */
class EntryState : public State {
public:
    /**
     * @brief Construct a new EntryState
     * @param context State context
     */
    explicit EntryState(StateContext& context);
    
    /**
     * @brief Destructor
     */
    virtual ~EntryState() = default;
    
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
     * @brief Transition to main menu
     */
    void transitionToMainMenu();

    UI::Label m_titleLabel;              ///< Title label
    UI::Label m_pressKeyLabel;           ///< "Press any key" label
    sf::RectangleShape m_background;      ///< Background
    sf::Clock m_clock;                    ///< Timer for animations
    float m_elapsedTime = 0.0f;          ///< Elapsed time since entry
    bool m_pressKeyVisible = true;       ///< Visibility flag for blinking text
    static constexpr float AUTO_ADVANCE_TIME = 3.0f;  ///< Auto-advance after 3 seconds
    static constexpr float BLINK_INTERVAL = 0.5f;     ///< Blink interval in seconds
};

} // namespace DSA
