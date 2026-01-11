/**
 * @file Button.cpp
 * @brief Implementation of Button component
 */

#include "Button.h"
#include "../Theme/ThemeManager.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>

namespace DSA {
namespace UI {

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text)
    : m_shape(size)
    , m_state(ButtonState::Normal)
    , m_enabled(true)
{
    m_shape.setPosition(position);
    setText(text);
    
    // Set initial appearance
    updateAppearance();
}

void Button::setText(const std::string& text) {
    // SFML 3.0: Text requires font in constructor
    try {
        ThemeManager& tm = ThemeManager::getInstance();
        tm.loadFonts();
        const sf::Font& font = tm.getMainFont();
        
        // Create text with font (SFML 3.0 requirement)
        m_text.emplace(font, text, 24);
        centerText();
    } catch (...) {
        // Font not available, reset text
        m_text.reset();
    }
}

std::string Button::getText() const {
    if (m_text.has_value()) {
        return m_text->getString();
    }
    return "";
}

void Button::setPosition(const sf::Vector2f& position) {
    m_shape.setPosition(position);
    centerText();
}

sf::Vector2f Button::getPosition() const {
    return m_shape.getPosition();
}

void Button::setSize(const sf::Vector2f& size) {
    m_shape.setSize(size);
    centerText();
}

sf::Vector2f Button::getSize() const {
    return m_shape.getSize();
}

void Button::setCallback(std::function<void()> callback) {
    m_callback = std::move(callback);
}

void Button::trigger() {
    if (m_enabled && m_callback) {
        m_callback();
    }
}

void Button::setEnabled(bool enabled) {
    m_enabled = enabled;
    if (!m_enabled) {
        m_state = ButtonState::Disabled;
    }
    updateAppearance();
}

bool Button::isEnabled() const {
    return m_enabled;
}

bool Button::handleInput(const sf::Event& event, const sf::Vector2f& mousePosition) {
    if (!m_enabled) {
        return false;
    }
    
    m_mousePosition = mousePosition;
    bool isInside = contains(mousePosition);
    
    // Handle mouse button pressed
    if (event.is<sf::Event::MouseButtonPressed>()) {
        auto mouseData = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseData && mouseData->button == sf::Mouse::Button::Left && isInside) {
            m_state = ButtonState::Pressed;
            updateAppearance();
            return true;
        }
    }
    
    // Handle mouse button released
    if (event.is<sf::Event::MouseButtonReleased>()) {
        auto mouseData = event.getIf<sf::Event::MouseButtonReleased>();
        if (mouseData && mouseData->button == sf::Mouse::Button::Left) {
            if (m_state == ButtonState::Pressed && isInside) {
                // Button was clicked
                if (m_callback) {
                    m_callback();
                }
            }
            m_state = isInside ? ButtonState::Hovered : ButtonState::Normal;
            updateAppearance();
            return m_state == ButtonState::Normal || m_state == ButtonState::Hovered;
        }
    }
    
    return false;
}

void Button::update(const sf::Vector2f& mousePosition) {
    if (!m_enabled) {
        return;
    }
    
    m_mousePosition = mousePosition;
    bool isInside = contains(mousePosition);
    
    if (m_state != ButtonState::Pressed) {
        m_state = isInside ? ButtonState::Hovered : ButtonState::Normal;
        updateAppearance();
    }
}

void Button::render(sf::RenderTarget& target) const {
    target.draw(m_shape);
    if (m_text.has_value()) {
        target.draw(*m_text);
    }
}

bool Button::contains(const sf::Vector2f& point) const {
    sf::FloatRect bounds = m_shape.getGlobalBounds();
    return bounds.contains(point);
}

bool Button::isHovered() const {
    return m_state == ButtonState::Hovered;
}

bool Button::isPressed() const {
    return m_state == ButtonState::Pressed;
}

void Button::updateAppearance() {
    ThemeManager& tm = ThemeManager::getInstance();
    const Theme& theme = tm.getTheme();
    
    if (m_text.has_value()) {
        switch (m_state) {
            case ButtonState::Normal:
                m_shape.setFillColor(theme.primaryColor);
                // Use white text for better visibility on dark backgrounds
                m_text->setFillColor(sf::Color::White);
                break;
            case ButtonState::Hovered:
                m_shape.setFillColor(theme.hoverColor);
                m_text->setFillColor(sf::Color::White);
                break;
            case ButtonState::Pressed:
                m_shape.setFillColor(theme.pressedColor);
                m_text->setFillColor(sf::Color::White);
                break;
            case ButtonState::Disabled:
                m_shape.setFillColor(theme.disabledColor);
                m_text->setFillColor(sf::Color(200, 200, 200)); // Light gray for disabled
                break;
        }
    } else {
        // No text, just set shape colors
        switch (m_state) {
            case ButtonState::Normal:
                m_shape.setFillColor(theme.primaryColor);
                break;
            case ButtonState::Hovered:
                m_shape.setFillColor(theme.hoverColor);
                break;
            case ButtonState::Pressed:
                m_shape.setFillColor(theme.pressedColor);
                break;
            case ButtonState::Disabled:
                m_shape.setFillColor(theme.disabledColor);
                break;
        }
    }
}

void Button::centerText() {
    if (!m_text.has_value()) {
        return;
    }
    
    sf::FloatRect textBounds = m_text->getLocalBounds();
    sf::FloatRect shapeBounds = m_shape.getGlobalBounds();
    
    m_text->setPosition(sf::Vector2f(
        shapeBounds.position.x + (shapeBounds.size.x - textBounds.size.x) / 2.0f - textBounds.position.x,
        shapeBounds.position.y + (shapeBounds.size.y - textBounds.size.y) / 2.0f - textBounds.position.y
    ));
}

} // namespace UI
} // namespace DSA
