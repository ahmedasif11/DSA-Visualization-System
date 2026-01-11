

#include "Label.h"
#include "../Theme/ThemeManager.h"

namespace DSA {
namespace UI {

Label::Label(const sf::Vector2f& position, const std::string& text)
{
    setPosition(position);
    setText(text);
}

void Label::setText(const std::string& text) {

    try {
        ThemeManager& tm = ThemeManager::getInstance();
        tm.loadFonts();
        const sf::Font& font = tm.getMainFont();
        const Theme& theme = tm.getTheme();

        m_text.emplace(font, text, theme.fontSizeNormal);
        m_text->setFillColor(theme.textColor);
    } catch (...) {

        m_text.reset();
    }
}

std::string Label::getText() const {
    if (m_text.has_value()) {
        return m_text->getString();
    }
    return "";
}

void Label::setPosition(const sf::Vector2f& position) {
    if (m_text.has_value()) {
        m_text->setPosition(position);
    }
}

sf::Vector2f Label::getPosition() const {
    if (m_text.has_value()) {
        return m_text->getPosition();
    }
    return sf::Vector2f(0, 0);
}

void Label::setFontSize(unsigned int size) {
    if (m_text.has_value()) {
        m_text->setCharacterSize(size);
    }
}

unsigned int Label::getFontSize() const {
    if (m_text.has_value()) {
        return m_text->getCharacterSize();
    }
    return 0;
}

void Label::setColor(const sf::Color& color) {
    if (m_text.has_value()) {
        m_text->setFillColor(color);
    }
}

sf::Color Label::getColor() const {
    if (m_text.has_value()) {
        return m_text->getFillColor();
    }
    return sf::Color::Black;
}

void Label::render(sf::RenderTarget& target) const {
    if (m_text.has_value()) {
        target.draw(*m_text);
    }
}

sf::FloatRect Label::getLocalBounds() const {
    if (m_text.has_value()) {
        return m_text->getLocalBounds();
    }
    return sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
}

}
} 
