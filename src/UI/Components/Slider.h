#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <functional>

namespace DSA {
namespace UI {

class Slider {
public:
    Slider(const sf::Vector2f& position, float width, float minValue, float maxValue, float defaultValue = 1.0f);
    virtual ~Slider() = default;
    
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    
    void setValue(float value);
    float getValue() const;
    
    void setMinValue(float minValue);
    void setMaxValue(float maxValue);
    
    void setCallback(std::function<void(float)> callback);
    
    bool handleInput(const sf::Event& event, const sf::Vector2f& mousePosition);
    void update(const sf::Vector2f& mousePosition);
    void render(sf::RenderTarget& target) const;
    
    bool isDragging() const { return m_isDragging; }
    bool contains(const sf::Vector2f& point) const;

private:
    void updateAppearance();
    void updateHandlePosition();
    float valueFromPosition(float x) const;
    float positionFromValue(float value) const;

    sf::Vector2f m_position;
    float m_width;
    float m_height;
    float m_minValue;
    float m_maxValue;
    float m_value;
    
    bool m_isDragging;
    bool m_isHovered;
    
    std::function<void(float)> m_callback;
    
    sf::RectangleShape m_track;
    sf::RectangleShape m_fill;
    sf::RectangleShape m_handle;
    
    sf::Vector2f m_mousePosition;
};

}
}
