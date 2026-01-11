/**
 * @file Label.h
 * @brief Label UI component (simple text display)
 */

#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include <optional>

namespace DSA {
namespace UI {

/**
 * @class Label
 * @brief Simple text label component
 * 
 * Displays text with theme styling.
 */
class Label {
public:
    /**
     * @brief Construct a new Label
     * @param position Label position (default: 0,0)
     * @param text Label text (default: empty)
     */
    Label(const sf::Vector2f& position = sf::Vector2f(0, 0), const std::string& text = "");
    
    /**
     * @brief Destructor
     */
    virtual ~Label() = default;
    
    /**
     * @brief Set label text
     * @param text The text to display
     */
    void setText(const std::string& text);
    
    /**
     * @brief Get label text
     * @return The label text
     */
    std::string getText() const;
    
    /**
     * @brief Set label position
     * @param position The new position
     */
    void setPosition(const sf::Vector2f& position);
    
    /**
     * @brief Get label position
     * @return The label position
     */
    sf::Vector2f getPosition() const;
    
    /**
     * @brief Set font size
     * @param size Font size in pixels
     */
    void setFontSize(unsigned int size);
    
    /**
     * @brief Get font size
     * @return Font size in pixels
     */
    unsigned int getFontSize() const;
    
    /**
     * @brief Set text color
     * @param color Text color
     */
    void setColor(const sf::Color& color);
    
    /**
     * @brief Get text color
     * @return Text color
     */
    sf::Color getColor() const;
    
    /**
     * @brief Render label to target
     * @param target The render target
     */
    void render(sf::RenderTarget& target) const;
    
    /**
     * @brief Get text bounds
     * @return Text local bounds
     */
    sf::FloatRect getLocalBounds() const;

private:
    std::optional<sf::Text> m_text;    ///< Text object (optional for SFML 3.0)
};

} // namespace UI
} // namespace DSA
