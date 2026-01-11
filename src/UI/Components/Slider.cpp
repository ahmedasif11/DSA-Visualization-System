#include "Slider.h"
#include "../../App/Config.h"
#include "../../UI/Theme/ThemeManager.h"
#include <algorithm>
#include <cmath>

namespace DSA {
namespace UI {

Slider::Slider(const sf::Vector2f& position, float width, float minValue, float maxValue, float defaultValue)
    : m_position(position)
    , m_width(width)
    , m_height(20.0f)
    , m_minValue(minValue)
    , m_maxValue(maxValue)
    , m_value(defaultValue)
    , m_isDragging(false)
    , m_isHovered(false)
{
    m_track.setSize(sf::Vector2f(m_width, m_height));
    m_track.setPosition(m_position);
    m_track.setFillColor(sf::Color(60, 60, 70));
    m_track.setOutlineColor(sf::Color(100, 100, 110));
    m_track.setOutlineThickness(2.0f);
    
    m_fill.setSize(sf::Vector2f(0, m_height));
    m_fill.setPosition(m_position);
    m_fill.setFillColor(sf::Color(Config::Colors::ACCENT_R, Config::Colors::ACCENT_G, Config::Colors::ACCENT_B));
    
    float handleSize = m_height + 6.0f;
    m_handle.setSize(sf::Vector2f(handleSize, handleSize));
    m_handle.setPosition(m_position);
    m_handle.setFillColor(sf::Color(Config::Colors::PRIMARY_R, Config::Colors::PRIMARY_G, Config::Colors::PRIMARY_B));
    m_handle.setOutlineColor(sf::Color(Config::Colors::ACCENT_R, Config::Colors::ACCENT_G, Config::Colors::ACCENT_B));
    m_handle.setOutlineThickness(2.0f);
    
    updateHandlePosition();
    updateAppearance();
}

void Slider::setPosition(const sf::Vector2f& position) {
    m_position = position;
    m_track.setPosition(m_position);
    m_fill.setPosition(m_position);
    updateHandlePosition();
}

sf::Vector2f Slider::getPosition() const {
    return m_position;
}

void Slider::setValue(float value) {
    m_value = std::clamp(value, m_minValue, m_maxValue);
    updateHandlePosition();
    updateAppearance();
}

float Slider::getValue() const {
    return m_value;
}

void Slider::setMinValue(float minValue) {
    m_minValue = minValue;
    setValue(m_value);
}

void Slider::setMaxValue(float maxValue) {
    m_maxValue = maxValue;
    setValue(m_value);
}

void Slider::setCallback(std::function<void(float)> callback) {
    m_callback = callback;
}

bool Slider::handleInput(const sf::Event& event, const sf::Vector2f& mousePosition) {
    m_mousePosition = mousePosition;
    
    if (event.is<sf::Event::MouseButtonPressed>()) {
        const auto* mouseData = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseData && mouseData->button == sf::Mouse::Button::Left) {
            if (contains(mousePosition) || m_isDragging) {
                m_isDragging = true;
                float newValue = valueFromPosition(mousePosition.x);
                setValue(newValue);
                if (m_callback) {
                    m_callback(m_value);
                }
                return true;
            }
        }
    }
    
    if (event.is<sf::Event::MouseButtonReleased>()) {
        const auto* mouseData = event.getIf<sf::Event::MouseButtonReleased>();
        if (mouseData && mouseData->button == sf::Mouse::Button::Left) {
            if (m_isDragging) {
                m_isDragging = false;
                return true;
            }
        }
    }
    
    return false;
}

void Slider::update(const sf::Vector2f& mousePosition) {
    m_mousePosition = mousePosition;
    
    bool wasHovered = m_isHovered;
    m_isHovered = contains(mousePosition) || m_isDragging;
    
    if (wasHovered != m_isHovered) {
        updateAppearance();
    }
    
    if (m_isDragging) {
        float newValue = valueFromPosition(mousePosition.x);
        float oldValue = m_value;
        setValue(newValue);
        if (m_callback && std::abs(oldValue - m_value) > 0.01f) {
            m_callback(m_value);
        }
    }
}

void Slider::render(sf::RenderTarget& target) const {
    target.draw(m_track);
    target.draw(m_fill);
    target.draw(m_handle);
}

bool Slider::contains(const sf::Vector2f& point) const {
    return point.x >= m_position.x - 10.0f &&
           point.x <= m_position.x + m_width + 10.0f &&
           point.y >= m_position.y - 10.0f &&
           point.y <= m_position.y + m_height + 10.0f;
}

void Slider::updateAppearance() {
    if (m_isDragging || m_isHovered) {
        m_handle.setOutlineThickness(3.0f);
        m_handle.setFillColor(sf::Color(Config::Colors::ACCENT_R, Config::Colors::ACCENT_G, Config::Colors::ACCENT_B));
    } else {
        m_handle.setOutlineThickness(2.0f);
        m_handle.setFillColor(sf::Color(Config::Colors::PRIMARY_R, Config::Colors::PRIMARY_G, Config::Colors::PRIMARY_B));
    }
}

void Slider::updateHandlePosition() {
    float handleX = positionFromValue(m_value);
    float handleSize = m_height + 6.0f;
    m_handle.setPosition(sf::Vector2f(handleX - handleSize / 2.0f, m_position.y - 3.0f));
    
    float fillWidth = handleX - m_position.x;
    m_fill.setSize(sf::Vector2f(std::max(0.0f, fillWidth), m_height));
}

float Slider::valueFromPosition(float x) const {
    float relativeX = x - m_position.x;
    float ratio = std::clamp(relativeX / m_width, 0.0f, 1.0f);
    return m_minValue + ratio * (m_maxValue - m_minValue);
}

float Slider::positionFromValue(float value) const {
    float ratio = (value - m_minValue) / (m_maxValue - m_minValue);
    ratio = std::clamp(ratio, 0.0f, 1.0f);
    return m_position.x + ratio * m_width;
}

}
}
