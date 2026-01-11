/**
 * @file TestState.h
 * @brief Test state for Phase 1 verification
 */

#pragma once

#include "../Core/State/State.h"
#include "../Core/State/StateID.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <string>
#include <optional>

namespace DSA {

/**
 * @class TestState
 * @brief Simple test state for Phase 1 verification
 * 
 * Displays a simple message and allows state switching
 */
class TestState : public State {
public:
    /**
     * @brief Construct a new TestState
     * @param context State context
     * @param message Message to display
     */
    explicit TestState(StateContext& context, const std::string& message = "Test State");
    
    /**
     * @brief Destructor
     */
    virtual ~TestState() = default;
    
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
    std::string m_message;                    ///< Display message
    std::optional<sf::Text> m_text;          ///< Text to display (optional to defer initialization)
    sf::RectangleShape m_background;         ///< Background rectangle
    bool m_initialized;                      ///< Initialization flag
};

} // namespace DSA
