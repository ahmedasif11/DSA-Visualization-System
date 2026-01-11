/**
 * @file Button.h
 * @brief Button UI component
 */

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <string>
#include <optional>

namespace DSA {
namespace UI {

/**
 * @enum ButtonState
 * @brief Button state enumeration
 */
enum class ButtonState {
    Normal,     ///< Normal state
    Hovered,    ///< Mouse hover state
    Pressed,    ///< Mouse pressed state
    Disabled    ///< Disabled state
};

/**
 * @class Button
 * @brief Reusable button component
 * 
 * Handles mouse interactions, states, and callbacks.
 */
class Button {
public:
    /**
     * @brief Construct a new Button
     * @param position Button position
     * @param size Button size
     * @param text Button text
     */
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text = "");
    
    /**
     * @brief Destructor
     */
    virtual ~Button() = default;
    
    /**
     * @brief Set button text
     * @param text The text to display
     */
    void setText(const std::string& text);
    
    /**
     * @brief Get button text
     * @return The button text
     */
    std::string getText() const;
    
    /**
     * @brief Set button position
     * @param position The new position
     */
    void setPosition(const sf::Vector2f& position);
    
    /**
     * @brief Get button position
     * @return The button position
     */
    sf::Vector2f getPosition() const;
    
    /**
     * @brief Set button size
     * @param size The new size
     */
    void setSize(const sf::Vector2f& size);
    
    /**
     * @brief Get button size
     * @return The button size
     */
    sf::Vector2f getSize() const;
    
    /**
     * @brief Set button callback
     * @param callback Function to call when button is clicked
     */
    void setCallback(std::function<void()> callback);
    
    /**
     * @brief Trigger button click (call callback directly)
     * Useful for keyboard navigation
     */
    void trigger();
    
    /**
     * @brief Enable or disable the button
     * @param enabled true to enable, false to disable
     */
    void setEnabled(bool enabled);
    
    /**
     * @brief Check if button is enabled
     * @return true if enabled
     */
    bool isEnabled() const;
    
    /**
     * @brief Handle input event
     * @param event The SFML event
     * @param mousePosition Current mouse position
     * @return true if event was handled
     */
    bool handleInput(const sf::Event& event, const sf::Vector2f& mousePosition);
    
    /**
     * @brief Update button state (call each frame)
     * @param mousePosition Current mouse position
     */
    void update(const sf::Vector2f& mousePosition);
    
    /**
     * @brief Render button to target
     * @param target The render target
     */
    void render(sf::RenderTarget& target) const;
    
    /**
     * @brief Check if point is inside button
     * @param point The point to check
     * @return true if point is inside
     */
    bool contains(const sf::Vector2f& point) const;
    
    /**
     * @brief Check if button is hovered
     * @return true if hovered
     */
    bool isHovered() const;
    
    /**
     * @brief Check if button is pressed
     * @return true if pressed
     */
    bool isPressed() const;

private:
    /**
     * @brief Update button appearance based on state
     */
    void updateAppearance();
    
    /**
     * @brief Center text in button
     */
    void centerText();

    sf::RectangleShape m_shape;              ///< Button rectangle
    std::optional<sf::Text> m_text;          ///< Button text (optional for SFML 3.0)
    ButtonState m_state = ButtonState::Normal; ///< Current state
    bool m_enabled = true;                   ///< Enabled flag
    std::function<void()> m_callback;        ///< Click callback
    sf::Vector2f m_mousePosition;            ///< Current mouse position
};

} // namespace UI
} // namespace DSA
