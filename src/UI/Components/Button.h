

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <string>
#include <optional>

namespace DSA {
namespace UI {


enum class ButtonState {
    Normal,
    Hovered,
    Pressed,
    Disabled
};


class Button {
public:
    
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text = "");
    
    
    virtual ~Button() = default;
    
    
    void setText(const std::string& text);
    
    
    std::string getText() const;
    
    
    void setPosition(const sf::Vector2f& position);
    
    
    sf::Vector2f getPosition() const;
    
    
    void setSize(const sf::Vector2f& size);
    
    
    sf::Vector2f getSize() const;
    
    
    void setCallback(std::function<void()> callback);
    
    
    void trigger();
    
    
    void setEnabled(bool enabled);
    
    
    bool isEnabled() const;
    
    
    bool handleInput(const sf::Event& event, const sf::Vector2f& mousePosition);
    
    
    void update(const sf::Vector2f& mousePosition);
    
    
    void render(sf::RenderTarget& target) const;
    
    
    bool contains(const sf::Vector2f& point) const;
    
    
    bool isHovered() const;
    
    
    bool isPressed() const;

private:
    
    void updateAppearance();
    
    
    void centerText();

    sf::RectangleShape m_shape;
    std::optional<sf::Text> m_text;
    ButtonState m_state = ButtonState::Normal;
    bool m_enabled = true;
    std::function<void()> m_callback;
    sf::Vector2f m_mousePosition;
};

}
} 
